#include <assert.h>
#include "graph_point.h"

graph_point * graph_point_add(graph_point *point, const int x, const int y) {
  /* Allocate memory for new point */
  graph_point *newPoint = (graph_point *) malloc(sizeof(graph_point));
  *(int *)&newPoint->x = x;
  *(int *)&newPoint->y = y;
  /* If no point is specified, we are starting a new linked list */
  /* Otherwise we need to work out where to place the new element */
  if (point) {
    /* Do we need to move forward? */
    while (point->next && x >= point->next->x) {
      point = point->next;
    }
    /* Do we need to move backwards? */
    while (point->prev && x < point->x) {
      point = point->prev;
    }
    if (x < point->x) {
      /* We can assert that there is no previous - this will be the new tail */
      assert(!point->prev);
      /* Since this will be the new tail, lets set prev of point to newPoint */
      point->prev = newPoint;
      /* Point will in turn be the next of the newPoint */
      newPoint->next = point;
    } else if (x > point->x) {
      /* newPoint comes next in the list */
      /* Check if the current point is the head */
      if (point->next) {
        /* Not the head, need to insert between this and next */
        newPoint->prev = point;
        newPoint->next = point->next;
        /* Update the next point's prev */
        point->next->prev = newPoint;
        /* Update the point's next */
        point->next = newPoint;
      } else {
        /* Is the head, set this as the new head */
        point->next = newPoint;
        /* Point will in turn be the prev of the newPoint */
        newPoint->prev = point;
      }
    } else {
      /* newPoint must be equal the current point */
      assert(x == point->x);
      /* Replace the point */
      /* Set next and prev as with current point */
      newPoint->next = point->next;
      newPoint->prev = point->prev;
      /* Free the old point from memory */
      free(point);
    }
  }
  return newPoint;
}
