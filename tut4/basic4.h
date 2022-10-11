#ifndef __BASIC4_H__
#define __BASIC4_H__

#include <gst/gst.h>

/* Structure to contain all our information, so we can pass it around */
typedef struct PlayerData_t {
  GstElement *playbin;  /* Our one and only element */
  gboolean playing;      /* Are we in the PLAYING state? */
  gboolean terminate;    /* Should we terminate execution? */
  gboolean seek_enabled; /* Is seeking enabled for this media? */
  gboolean seek_done;    /* Have we performed the seek already? */
  gint64 duration;       /* How long does this media last, in nanoseconds */
} PlayerData;

char Player_init(PlayerData *);

/* Forward definition of the message processing function */
void Player_handleMessage(PlayerData *, GstMessage *);


#endif
