#include "../lcd/lcd.h"
#include <stdbool.h>
#include "graph_point.h"

typedef struct graph_plot graph_plot;
typedef struct graph graph;

struct graph {
	lcd *display;
  rectangle *drawingArea;
  char *title[48];
  char *xAxisLabel[32];
  char *yAxisLabel[32];
  double minX, maxX, minY, maxY;
  bool drawn;
  bool autoScaleX, autoScaleY, autoPanX, autoPanY;
  bool loopX, loopY;
  int loopOverPointX, loopOverPointY;
  graph_plot **plots[8];
};

struct graph_plot {
  const graph *graph;
  const uint16_t color;
  /* Next value */
  graph_point *head;
  /* Previous value */
  graph_point *tail;
  int x_offset;
  int y_offset;
  bool joinPoints;
  double (*f)(double);
};

/* Initialise a new graph */
graph * graph_create(lcd *display);

/* Set the area which the graph should be drawn */
void graph_setDrawingArea(graph *graph, rectangle *area);

/* Set graph text */
void graph_setTitle(graph *graph, char *title);
void graph_setXAxisLabel(graph *graph, char *label);
void graph_setYAxisLabel(graph *graph, char *label);

/* Set graph ranges */
void graph_setXAxisRange(graph *graph, double min, double max);
void graph_setYAxisRange(graph *graph, double min, double max);

/* Set boolean options */
void graph_setAutoScaleX(graph *graph, bool autoScale);
void graph_setAutoScaleY(graph *graph, bool autoScale);
void graph_setAutoPanX(graph *graph, bool autoPan);
void graph_setAutoPanY(graph *graph, bool autoPan);

/* Draw the graph, to be called once all settings have been set */
/* Once drawn, changes to settings will happen imediately */
void graph_draw(graph *graph);
/* Redraw completely */
void graph_redraw(graph *graph);

/* Pan the graph */
void graph_panX(graph *graph, double panX);
void graph_panY(graph *graph, double panX);

/* Initialise a new graph plot */
graph_plot * graph_create_plot(graph *graph, uint16_t color);

/* Graph plot options */
void graph_plotJoinPoints(graph *graph, bool set);

/* Plot a point on graph */
void graph_plotPoint(graph_plot *plot, double x, double y);
void graph_plotNext(graph_plot *plot, double y);
void graph_plotFunc(graph_plot *plot, double (*f)(double));
