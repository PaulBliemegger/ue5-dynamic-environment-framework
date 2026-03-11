# Dynamic Environemt Loop - DEL

## Thesis

## Repository

### Overview

### Setup

### Binding to LogAction delegate

This is useful in order to react to changes in the Action log history. You can do so via events.
IMPORTANT: You need to unbind from the event!! This is since the `DELWorldStateSubsystem` is a `UGameInstanceSubsystem` and therfore does not automatically unbind after exit.
