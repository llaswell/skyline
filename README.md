# skyline
Solution to skyline interview question

This is my solution to the Skyline problem as defined here:

http://www.algorithmist.com/index.php/UVa_105

My solution has avergage execution complexity of O(n)

Brief description:

Intuitively, as we add many buildings to the skyline, most of them are covered.  Once a building is covered, it becomes irrelevant to drawing the skyline silhouette.  We take advantage of this fact to produce a more efficient algorithm.

We maintain a sorted list of buildings that are disjoint.  For each building encountered, we add it to the list by checking for overlap with buildings already on the list.  If a building already on the list is covered by the new building, we remove it.  If the new building is covered by an existing building, it is discarded.  If there is a partial overlap, the buildings are resized so there is no overlap.  For "realistic" building sizes, this results in a relatively small list that must be checked and because we maintain only disjoint buildings, the interactions are simple.  The worst case performance occurs when we have many very narrow buildings(a city of needles).

