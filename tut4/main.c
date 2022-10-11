#include "basic4.h"
#include "stdlib.h"

int main(int argc, char *argv[]) {
  PlayerData *data = malloc(sizeof(PlayerData));
  GstBus *bus;
  GstMessage *msg;
  GstStateChangeReturn ret;

	g_print("data_outside = %p\n", data);
		/* Initialize GStreamer */
	gst_init(&argc, &argv);

	if (!Player_init(data))
	{
		return -1;
	}

	// char uri[] = "https://www.youtube.com/watch?v=ioNng23DkIM"; 
	char uri[] = "https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm"; 

  /* Set the URI to play */
  g_object_set (data->playbin, "uri", uri, NULL);

  /* Start playing */
  ret = gst_element_set_state (data->playbin, GST_STATE_PLAYING);
  if (ret == GST_STATE_CHANGE_FAILURE) {
    g_printerr ("Unable to set the pipeline to the playing state.\n");
    gst_object_unref (data->playbin);
    return -1;
  }

  /* Listen to the bus */
  bus = gst_element_get_bus (data->playbin);
  do {
    msg = gst_bus_timed_pop_filtered (bus, 100 * GST_MSECOND,
        GST_MESSAGE_STATE_CHANGED | GST_MESSAGE_ERROR | GST_MESSAGE_EOS | GST_MESSAGE_DURATION);

    /* Parse message */
    if (msg != NULL) {
      Player_handleMessage (data, msg);
    } else {
      /* We got no message, this means the timeout expired */
      if (data->playing) {
        gint64 current = -1;

        /* Query the current position of the stream */
        if (!gst_element_query_position (data->playbin, GST_FORMAT_TIME, &current)) {
          g_printerr ("Could not query current position.\n");
        }

        /* If we didn't know it yet, query the stream duration */
        if (!GST_CLOCK_TIME_IS_VALID (data->duration)) {
          if (!gst_element_query_duration (data->playbin, GST_FORMAT_TIME, &data->duration)) {
            g_printerr ("Could not query current duration.\n");
          }
        }

        /* Print current position and total duration */
        g_print ("Position %" GST_TIME_FORMAT " / %" GST_TIME_FORMAT "\r",
            GST_TIME_ARGS (current), GST_TIME_ARGS (data->duration));

        /* If seeking is enabled, we have not done it yet, and the time is right, seek */
        if (data->seek_enabled && !data->seek_done && current > 10 * GST_SECOND) {
          g_print ("\nReached 10s, performing seek...\n");
          gst_element_seek_simple (data->playbin, GST_FORMAT_TIME,
              GST_SEEK_FLAG_FLUSH | GST_SEEK_FLAG_KEY_UNIT, current + 30 * GST_SECOND);
          data->seek_done = TRUE;
        }
      }
    }
  } while (!data->terminate);

  /* Free resources */
  gst_object_unref (bus);
  gst_element_set_state (data->playbin, GST_STATE_NULL);
  gst_object_unref (data->playbin);
  return 0;
}

