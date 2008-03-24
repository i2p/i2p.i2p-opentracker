/* This software was written by Dirk Engling <erdgeist@erdgeist.org>
   It is considered beerware. Prost. Skol. Cheers or whatever.
   
   $id$ */

#ifndef __OT_TRACKERLOGIC_H__
#define __OT_TRACKERLOGIC_H__

#include <sys/types.h>
#include <sys/time.h>
#include <time.h>
#include <stdint.h>

typedef uint8_t        ot_hash[20];
typedef time_t         ot_time;

/* Some tracker behaviour tunable */
#define OT_CLIENT_TIMEOUT 60
#define OT_CLIENT_TIMEOUT_CHECKINTERVAL 10
#define OT_CLIENT_TIMEOUT_SEND (60*15)
#define OT_CLIENT_REQUEST_INTERVAL (60*15)
#define OT_CLIENT_REQUEST_VARIATION (60*6)

#define OT_TORRENT_TIMEOUT_HOURS 24
#define OT_TORRENT_TIMEOUT ((60*60*OT_TORRENT_TIMEOUT_HOURS)/OT_POOLS_TIMEOUT)

/* Be sure and fix static_outbuf size in ot_http if you increase the max...
   The announce reply size is _about_ the 80 byte http header, plus
   60 bytes of bencoded stuff, plus 580 bytes per peer.
 */
#define OT_NUMWANT_DEFAULT 20
#define OT_NUMWANT_MAX 54

/* i2psnark does randomization */
// #define OT_CLIENT_REQUEST_INTERVAL_RANDOM ( OT_CLIENT_REQUEST_INTERVAL - OT_CLIENT_REQUEST_VARIATION/2 + (int)( random( ) % OT_CLIENT_REQUEST_VARIATION ) )
#define OT_CLIENT_REQUEST_INTERVAL_RANDOM OT_CLIENT_REQUEST_INTERVAL

/* We maintain a list of 1024 pointers to sorted list of ot_torrent structs
   Sort key is, of course, its hash */
#define OT_BUCKET_COUNT 1024

/* Number of tracker admin ip addresses allowed */
#define OT_ADMINIP_MAX 64
#define OT_MAX_THREADS 16

/* This list points to 9 pools of peers each grouped in five-minute-intervals
   thus achieving a timeout of 2700s or 45 minutes
   These pools are sorted by its binary content */
#define OT_POOLS_COUNT   9
#define OT_POOLS_TIMEOUT (60*5)

/* From opentracker.c */
extern time_t g_now;
#define NOW              (g_now/OT_POOLS_TIMEOUT)

/* total is 520 + 2 + 20 + 2 = 544 */
/* 516 byte key + ".i2p" */
#define OT_DEST_SIZE 520
#define OT_DESTPORT_SIZE (OT_DEST_SIZE+2)
#define OT_ID_SIZE 20
#define OT_DESTPORTID_SIZE (OT_DESTPORT_SIZE+OT_ID_SIZE)
#define OT_TOTAL_SIZE (OT_DESTPORTID_SIZE+2)
typedef struct {
  uint8_t data[OT_TOTAL_SIZE];
} ot_peer;
static const uint8_t PEER_FLAG_SEEDING   = 0x80;
static const uint8_t PEER_FLAG_COMPLETED = 0x40;
static const uint8_t PEER_FLAG_STOPPED   = 0x20;

/* unused for i2p */
#define OT_SETIP( peer, ip ) memmove((peer),(ip),4);
/* overwrites IP */
#define OT_SETDEST( peer, ip ) memmove((peer),(ip),OT_DEST_SIZE);
#define OT_DEST(peer) ((uint8_t*)(peer))
#define OT_SETPORT( peer, port ) memmove(((uint8_t*)(peer))+OT_DEST_SIZE,(port),2);
#define OT_PORT(peer) *((uint16_t*)(((uint8_t*)(peer)) + OT_DEST_SIZE))
#define OT_SETID( peer, id ) memmove(((uint8_t*)(peer))+OT_DESTPORT_SIZE,(id),OT_ID_SIZE);
#define OT_ID(peer) (((uint8_t*)(peer)) + OT_DESTPORT_SIZE)
#define OT_FLAG(peer) (((uint8_t*)(peer))[OT_DESTPORTID_SIZE])

/* Port and ID are ignored, not used in comparisons */
#define OT_PEER_COMPARE_SIZE ((size_t) OT_DEST_SIZE)
#define OT_HASH_COMPARE_SIZE (sizeof(ot_hash))

struct ot_peerlist;
typedef struct ot_peerlist ot_peerlist;
typedef struct {
  ot_hash      hash;
  ot_peerlist *peer_list;
} ot_torrent;

#include "ot_vector.h"

struct ot_peerlist {
  ot_time        base;
  size_t         seed_count;
  size_t         peer_count;
  size_t         down_count;
  size_t         seed_counts[ OT_POOLS_COUNT ];
  ot_vector      peers[ OT_POOLS_COUNT ];
#ifdef WANT_TRACKER_SYNC
  ot_vector      changeset;
#endif
};

/*
   Exported functions
*/

#ifdef WANT_TRACKER_SYNC
#define WANT_TRACKER_SYNC_PARAM( param ) , param
#else
#define WANT_TRACKER_SYNC_PARAM( param )
#endif

int  trackerlogic_init( const char * const serverdir );
void trackerlogic_deinit( void );

ot_torrent *add_peer_to_torrent( ot_hash *hash, ot_peer *peer  WANT_TRACKER_SYNC_PARAM( int from_changeset ) );
size_t remove_peer_from_torrent( ot_hash *hash, ot_peer *peer, char *reply, int is_tcp );
size_t return_peers_for_torrent( ot_peer *peer, ot_hash *hash, size_t amount, char *reply, int is_tcp );
size_t return_tcp_scrape_for_torrent( ot_hash *hash, int amount, char *reply );
size_t return_udp_scrape_for_torrent( ot_hash *hash, char *reply );
int same_peer(ot_peer *a, ot_peer *b);

/* Helper, before it moves to its own object */
void free_peerlist( ot_peerlist *peer_list );

#endif
