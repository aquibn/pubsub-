# PubSub Project (Debug-Enhanced Version)

## Usage

1. Build the project:
```bash
make
```

2. Run in three terminals:
```bash
./server
./subscriber sports
./publisher pub1 sports "Test message"
```

3. Logs will show byte counts for each read/write to help diagnose buffering issues.

## Clean Up
```bash
make clean
```
# pubsub-
