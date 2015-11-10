# skyline
Solution to skyline interview question

This is my solution to the Skyline problem as defined here:

http://www.algorithmist.com/index.php/UVa_105

My solution has average execution complexity of O(n)

Brief description:

Intuitively, as we add many buildings to the skyline, most of them are covered.  Once a building is covered, it becomes irrelevant to drawing the skyline silhouette.  We take advantage of this fact to produce a more efficient algorithm.

We maintain a sorted list of buildings that are disjoint.  For each building encountered, we add it to the list by checking for overlap with buildings already on the list.  If a building already on the list is covered by the new building, we remove it.  If the new building is covered by an existing building, it is discarded.  If there is a partial overlap, the buildings are resized so there is no overlap.  For "realistic" building sizes, this results in a relatively small list that must be checked and because we maintain only disjoint buildings, the interactions are simple.  The worst case performance occurs when we have many very narrow buildings(a city of needles).

I have run and tested this on Mint Linux (an ubuntu variant) and (Amazon Linux).

The build.bash script should build 2 binaries.

I built with gcc 4.6.3 and gcc 4.8.3.

createBuildings is a utility for creating random sets of buildings to test performance against.
skyline takes a file defining buildings and outputs the coordinates for the skyline to stdout in the format expected by the problem.

After building you can run check.bash.  It runs against the data set provided in the original problem and displays the solution.  Below it displays the correct solution for comparison.

The script genFiles.bash generates building files ranging from size 10,000 buildings up to 1,000,000.  You can then check performance by running time.bash.  I used these scripts to check whether run time was linear (I believe it is, but check for yourself and let me know what you think).

