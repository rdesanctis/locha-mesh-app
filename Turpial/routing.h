#ifndef CONSENSUS_TYPES_H
#define CONSENSUS_TYPES_H

/**
 * @brief quality of a given link.
 * 
 */
typedef struct
{
    uint8_t last_rssi;     //  fuerza relativa de la señal.
    uint8_t last_snr;      //  relacion ruido / señal
    uint8_t response_time; //  el tiempo de respuesta entre mensaje enviado y llegada de ACK
} quality_link_t;

/**
 * @brief enums the packet type
 * 
 */
typedef enum packet_type_e
{
    NET_JOIN = 0,
    NET_BYE = 1,
    NET_ROUTE = 2,
    PACKET_ACK = 3,
    PACKET_MSG = 4,
    PACKET_TXN = 5,
    PACKET_HELLO = 6,
    PACKET_GOSSIP = 7
};

/**
 * @brief enums the given services of a peer
 * 
 */
typedef enum services_e
{
    PEER = 0,
    ROUTER = 1,   // offers as router for the locha mesh
    MSG_PUSH = 2, // offers as gateway for msgs, pushing msgs to internet??
    TX_PUSH = 3,  // offers as gateway for bitcoin txs, pushing txs by a dedicated service. sending ACK when the work it's done.
    ELECTRUM = 4,  // offers as a customized  electrum server.
    NODE_TYPE_PUBLIC = 5, // if node is open 
    NODE_TYPE_PRIVATE = 6 // if node is private 
};

/**
 * @brief constructs a packet
 * 
 */
typedef struct
{
    uint8_t max_hops;    // max_hops no entra en el calculo de hash.
    uint8_t length;      // longitud del mensaje.
    String from;        // direccion del remitente
    String to;          // enviamos el mensaje al id: to
    uint8_t sequence[2]; // por ejemplo {1, 2} representa parte 1 de 2 en total
    String payload; // es la secuencia del mensaje
    uint8_t msg_hash;    // first 4 bytes.
    packet_type_e type;
} packet_t;

/**
 * @brief structs neighbors table.
 * 
 */
typedef struct
{
    String id;         // uniqueid
    uint8_t offers[];       // servicios que ofrece
    uint8_t age;            // edad conocida
    uint8_t hops_away;      // saltos de distancia (metrica)
    quality_link_t quality; // calidad de enlace
} neighbor_entry_t;

/**
 * @brief struct, entry to route table.
 * 
 */
typedef struct
{
    neighbor_entry_t receiver;  // uniqueid del destinatario
    neighbor_entry_t next_neighbor; // unique id del vecino mas cercano
    uint8_t age;  // edad 
    quality_link_t vectors[];
} route_to_node_t;


typedef struct
{
  packet_t el_packet;
  uint8_t lastseen;
} packets_in_transit_t;

/**
 * @brief   enum the reasons.
 *          incomplete list!!
 * 
 */
typedef enum blacklisted_for
{
    BLOCK_FORWARD = 0,
    BLOCK_BACKWARD = 1,
    SPAMING = 2,
    FLOODING = 3
};

/**
 * @brief entry to blacklist table
 * 
 */
typedef struct
{
    neighbor_entry_t peer; // no creo q sea necesario duplicar este dato, con su id puede ser suficiente
    uint8_t reasons[];
    uint8_t since;
    uint8_t attempt;
    bool locked;
} blacklist_entry_t;

#endif // CONSENSUS_TYPES_H
