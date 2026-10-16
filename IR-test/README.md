# IR Receiver test

Just tested how to reveice IR signals from a remote.

I used LG AKB72915269 remote. The code basically receives and reads
signals from IR receiver and converts them to hex format.

- [Code](IR-test/IR-test.ino)
- [LG Remote key bindings](LG_AKB72915269_key_bindings.md)

## Wiring diagram

![Diagram](diagram.png)

# Relay controller

Same than above, but pressing remote button 1 turns relay on and button 2 turns relay off.

- [Code](IR-relay-controller/IR-relay-controller.ino)

![Diagram](diagram2.png)