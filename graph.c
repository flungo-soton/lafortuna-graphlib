#include "graph.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

#define CHECK_REDRAW if (graph->drawn) graph_redraw(graph);

graph * graph_create(lcd *display) {
  graph *graph = malloc(sizeof(graph));
  graph->display = display;
  graph->drawingArea.left = 0;
  graph->drawingArea.right = display->width - 1;
  graph->drawingArea.top = 0;
  graph->drawingArea.bottom = display->height - 1;
  /* No need to allocate any space for variables that might not be set */
  graph->title = NULL;
  graph->xAxisLabel = NULL;
  graph->yAxisLabel = NULL;
  graph->minX = -1;
  graph->maxX = 1;
  graph->minY = -1;
  graph->maxY = 1;
  graph->drawn = false;
  graph->autoScaleX = false;
  graph->autoScaleY = false;
  graph->autoPanX = false;
  graph->autoPanY = false;
  graph->loopX = false;
  graph->loopY = false;
  graph->loopOverPointX = 0;
  graph->loopOverPointY = 0;
  /* Keep pointer null until we actually assign */
  graph->plots = NULL;
  return graph;
}

void graph_setDrawingArea(graph *graph, rectangle area) {
  graph->drawingArea = area;
  CHECK_REDRAW
}

void graph_setTitle(graph *graph, char *title) {
  graph->title = &title;
  CHECK_REDRAW
}
void graph_setXAxisLabel(graph *graph, char *label) {
  graph->xAxisLabel = &label;
  CHECK_REDRAW
}
void graph_setYAxisLabel(graph *graph, char *label) {
  graph->yAxisLabel = &label;
  CHECK_REDRAW
}
