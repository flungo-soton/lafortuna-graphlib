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

typedef struct graph_point graph_point;

/* Bi-directional linked list for storing graph points */
struct graph_point {
  /* Pixel values for point */
  const int x, y;
  /* Actual values for point */
  double xv, yv;
  /* Next value */
  graph_point *next;
  /* Previous value */
  graph_point *prev;
};

/* Place a graph point within the list that `point` is a member of */
/* Automatically sorts by `x` value */
graph_point * graph_point_add(graph_point *point, const int x, const int y);

/* Trim the linked list of values less than x */
/* Returns the new tail */
graph_point * graph_point_trimLT(graph_point *point, double x);

/* Trim the linked list of values greater than x */
/* Returns the new head */
graph_point * graph_point_trimGT(graph_point *point, double x);

/* Remove a single graph point */
void graph_point_remove(graph_point *point);

/* Remove entire list */
void graph_point_removeAll(graph_point *point);
