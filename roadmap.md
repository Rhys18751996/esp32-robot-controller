# 🗺️ Roadmap (Clean, Ordered, Buildable — Refined)

## ⚙️ Phase 0 – Core System Skeleton (NEW)

**Goal:** Establish a solid foundation before features

### Tasks:
- Create repo
- create boilerplate folders and files for project
- Define core structures:

```cpp
struct Intent {
    float linear;    // -1.0 → 1.0
    float angular;   // -1.0 → 1.0
    bool boost;
    bool stop;
};

enum Mode {
    CONFIG,
    RUN
};

enum ControllerState {
    DISCONNECTED,
    CONNECTING,
    CONNECTED
};
```

- Implement fixed loop timing (non-blocking):

```cpp
const int LOOP_INTERVAL_MS = 20; // 50Hz
```

- Create basic update loop:

```cpp
void update() {
    readInputs();
    mapToIntent();
    applySafety();
    outputControl(); // stub for now
}
```

- Add lightweight logging layer:

```cpp
log(INFO, "System starting");
```

### Success Criteria:
- Stable loop timing
- Clean project structure
- Logging works

---

## ✅ Phase 1 – Bluetooth Controller (Input Layer)

**Goal:** Receive and understand controller input

### Tasks:
- Connect controller via Bluetooth (PS4Controller or BLE HID)
- Implement controller state machine
- Print all inputs to Serial
- Normalize values (-1.0 → 1.0)
- Add deadzone handling
- Add input smoothing:
```cpp
smoothed = alpha * new + (1 - alpha) * old;
```

### Success Criteria:
- Reliable connection
- No jitter
- Clean state transitions

---

## ✅ Phase 2 – Mapping System (Abstraction Layer)

**Goal:** Separate input from behavior

### Tasks:
- Define mapping JSON (config only)
- Parse JSON once at startup
- Convert to internal struct
- Build translation layer:
```
controller input → mapping → Intent
```

### Success Criteria:
- Mapping change requires no code change
- Outputs structured Intent

---

## ✅ Phase 3 – Preferences Storage (Persistence Layer)

**Goal:** Persist configuration safely

### Tasks:
- Use ESP32 Preferences (NVS)
- Store WiFi, mapping JSON, API endpoint
- Implement load/save
- Add validation + fallback defaults

### Success Criteria:
- Config survives reboot
- Invalid config safe

---

## ✅ Phase 4 – Web Server (Config Mode UI)

**Goal:** Configure device easily

### Tasks:
- Start AP (RobotConfig)
- Run lightweight web server
- Provide simple config pages
- Save via POST to NVS

### Success Criteria:
- Config accessible via phone
- Changes persist

---

## ✅ Phase 5 – Mode Switch Logic (System Control)

**Goal:** Clean separation of system modes

### Tasks:
- Toggle switch on GPIO
- Monitor continuously
- Add debounce (~200ms)
- Implement mode transitions

### Modes:
- Config Mode: AP + Web ON, Bluetooth OFF
- Run Mode: WiFi + Bluetooth ON, Web OFF

### Success Criteria:
- Stable switching
- No conflicts

---

## ✅ Phase 6 – API Communication (Cloud Integration)

**Goal:** Send intent data externally

### Tasks:
- Connect WiFi
- Send HTTP POST
- Fire-and-forget (no retry, no queue)
- Send at interval (e.g. 200ms)

### Success Criteria:
- Non-blocking
- No impact on control loop

---

## ✅ Phase 7 – Motor Control (Final Integration Layer)

**Goal:** Convert intent → movement

### Tasks:
- Setup motor driver
- PWM control
- Convert:
```cpp
left  = linear + angular;
right = linear - angular;
```

### Safety:
- Kill switch:
```cpp
if (noInputFor > 500ms) stopMotors();
```
- Stop on disconnect

### Success Criteria:
- Smooth motion
- Stable control
- Safe behavior

---

## 🔧 Design Decisions

- Typed intent model
- JSON only for config
- Fixed loop timing
- Fire-and-forget networking
- Runtime mode switching
- Logging layer

---

## ⚠️ Things to Watch

### Power Stability
- Separate supplies
- Common ground
- Add capacitor + regulator

### Bluetooth + WiFi
- Keep strict separation

### Controller Compatibility
- Test early

---

## 🚀 Future Expansion

- IMU
- Battery monitoring
- Autonomous modes
- OTA updates
- Camera
- Multi-robot systems