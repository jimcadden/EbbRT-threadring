# EbbRT-ThreadRing

EbbRT-ThreadRing is a distributed application that consists of a "ring" of
EbbRT backends which coordinate together to pass a token between the nodes. A
front-end process is responsible for setting up the ring , reporting the
status of the token, and eventually adding and removing nodes from the ring.  

### Requirements

Building this app requires the `socket` and `zookeeper` EbbRT libraries
available in the `/libs/` directory of the source repo.
