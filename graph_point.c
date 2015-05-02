#include <assert.h>
#include <stddef.h>
#include "graph_point.h"

graph_point * graph_point_add(graph_point *point, const int x, const int y) {
  /* Allocate memory for new point */
  graph_point *newPoint = (graph_point *) calloc(sizeof(graph_point));
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

graph_point * graph_point_trimLT(graph_point *start, double x) {
  /* Some additional places to store our pointers */
  graph_point *curr, *next;
  /* Move backwards until first value that is in the range we want to delete */
  while (start->xv < x) {
    start = start->prev;
  }
  /* Initialise pointers */
  curr = start;
  next = NULL;
  /* If there is a previous, lets store that in start so we can can clear
   * backwards after.
   */
  start = curr->prev;
  /* Move forwards deleting anything that is less than x */
  while (curr->xv < x) {
    next = curr->next;
    free(curr);
    curr = next;
  }
  if (next) {
    /* The last assignment of next will be the new head */
    next->next = NULL;
  }
  /* Move backwards from start deleting everything */
  /* NOT USING `next` to preserve value for return */
  while (start) {
    curr = start->prev;
    free(start);
    start = curr;
  }
  /* return new tail */
  return next;
}

graph_point * graph_point_trimGT(graph_point *start, double x) {
  /* Some additional places to store our pointers */
  graph_point *curr, *next;
  /* Move forwards until first value that is in the range we want to delete */
  while (start->xv > x) {
    start = start->next;
  }
  /* Some additional places to store our pointers */
  curr = start;
  next = NULL;
  /* If there is a next, lets store that in start so we can can clear
   * forwards after.
   */
  start = curr->next;
  /* Move backwards deleting anything that is less than x */
  while (curr->xv > x) {
    next = curr->prev;
    free(curr);
    curr = next;
  }
  if (next) {
    /* The last assignment of next will be the new head */
    next->next = NULL;
  }
  /* Move forwards from start deleting everything */
  /* NOT USING `next` to preserve value for return */
  while (start) {
    curr = start->next;
    free(start);
    start = curr;
  }
  /* return new head */
  return next;
}

void graph_point_remove(graph_point *point) {
  /* If point has a next, bridge to prev */
  if (point->next) {
    point->next->prev = point->prev;
  }
  /* If point has a prev, bridge to next */
  if (point->prev) {
    point->prev->next = point->next;
  }
  /* Free the space used by point */
  free(point);
}

void graph_point_removeAll(graph_point *start) {
  /* Some additional places to store our pointers */
  graph_point *curr = start->next; /* Keep start for now */
  graph_point *next;
  /* Go forward from curr */
  while (curr) {
    next = curr->next;
    free(curr);
    curr = next;
  }
  /* Go back from start */
  curr = start;
  while (curr) {
    next = curr->prev;
    free(curr);
    curr = next;
  }
}
