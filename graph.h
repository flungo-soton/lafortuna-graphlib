/* The MIT License (MIT)
 *
 * Copyright (c) 2015 Fabrizio Lungo <fab@lungo.co.uk>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include "../lcd/lcd.h"
#include <stdbool.h>
#include "graph_point.h"

#define GRAPH_PLOT_LIMIT 16;

typedef struct graph_plot graph_plot;
typedef struct graph graph;

struct graph {
	lcd *display;
  rectangle drawingArea;
  char** title;
  char** xAxisLabel;
  char** yAxisLabel;
  double minX, maxX, minY, maxY;
  bool drawn;
  bool autoScaleX, autoScaleY, autoPanX, autoPanY;
  bool loopX, loopY;
  int loopOverPointX, loopOverPointY;
  graph_plot** plots;
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
void graph_setDrawingArea(graph *graph, rectangle area);

/* Set graph text */
/* Arrays should be allocated in heap before passing and be a valid, null
 * terminated string.
 */
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
/* Clear the graph area */
void graph_clear(graph *graph);

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
