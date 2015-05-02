#include "graph.h"
#include <stddef.h>

graph * graph_create(lcd *display) {
  graph *graph = (graph *) malloc(sizeof(graph));
  graph->display = display;
  graph->drawingArea = { 0, 0, display.width, display.height };
  graph->title = NULL;
  graph->xAxisLabel = NULL;
  graph->yAxisLabel = NULL;
  graph->minX = -1;
  graph->maxX = 1;
  graph->minY = -1;
  graph->maxY = 1;
  graph->drawn = FALSE;
  graph->autoScaleX = FALSE;
  graph->autoScaleY = FALSE;
  graph->autoPanX = FALSE;
  graph->autoPanY = FALSE;
  graph->loopX = FALSE;
  graph->loopY = FALSE;
  graph->loopOverPointX = 0;
  graph->loopOverPointY = 0;
  /* Allocate space for 8 pointers to graph plots */
  graph->plots = (graph_plot **) calloc(8 * sizeof(graph_plot *));
  return graph;
}
