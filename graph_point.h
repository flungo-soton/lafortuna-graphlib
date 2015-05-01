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
