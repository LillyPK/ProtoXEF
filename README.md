# ProtoXEF
remote window software

## Current Status
**Early Development** - Contains a basic project structure with CMake build system and a functional Win32 UI framework.

## Planned Features
### Core Technology
- **QUIC Protocol** - Modern transport protocol built on UDP (2012)
  - Built in TLS encryption for secure connections
  - Multiplexing support without head-of-line blocking
  ![quic-blog-gcp-cloud-cdn-performance](https://github.com/user-attachments/assets/9cab73e5-3d9e-4274-ac57-e6e96cb1d9d4)
  - Congestion control
  - Client side toggle for TCP style ordering when needed
- **Windows Graphics Capture API** - GPU-accelerated screen capture
  - Minimal CPU overhead
  - High-performance frame capture
  - Per-window capture support

### Connection Flow

**QUIC Handshake (1-RTT)**
```
Client ────────────────────────────────────────────> Server
       Initial packet with TLS ClientHello
       + Connection setup

Client <──────────────────────────────────────────── Server
       Handshake complete + TLS ServerHello
       + Encrypted connection ready
```
*QUIC combines transport and TLS 1.3 handshake into a single round-trip, unlike TCP+TLS which requires 2-3 round-trips*

**Application Handshake**
```
Client ─────────> Server
       "are you there?"

Client <──────── Server
       "yes"
       (5 second timeout)

Client ─────────> Server
       {
          "auth_required": "true/false",
          "user_name": "changeme",
          "password": "changeme"
       }

Client <──────── Server
       "ok"
       + Window metadata
       + Session start
```

> **Note**: Authentication is designed for local network use only. Credentials are transmitted within the QUIC encrypted channel.

### Window Management Protocol

> **Note**: Authentication is designed for local network use only. Credentials are transmitted within the QUIC encrypted channel.

**Resize Window**
Client ─> Server:
```json
{
   "action": "window.update.size",
   "window": { "id": "abc123" },
   "size": { "width": 1280, "height": 720 }
}
```
Server ─> Client:
```json

{
   "action": "window.update.size",
   "window": { "id": "abc123" },
   "size": { "width": 1280, "height": 720 },
   "status": "applied"
}
```

**Update Title**
Client ─> Server:
```json
{
   "action": "window.update.title",
   "window": { "id": "abc123" },
   "title": "New Title"
}
```
Server ─> Client:
```json
{
   "action": "window.update.title",
   "window": { "id": "abc123" },
   "title": "New Title",
   "status": "updated"
}
```

**Close Window**
Client ─> Server:
```json
{
   "action": "window.update.close",
   "window": { "id": "abc123" }
}
```
Server ─> Client:
```json
{
   "action": "window.update.close",
   "window": { "id": "abc123" },
   "status": "closed"
}
```

> Window IDs correspond directly to Windows HWND handles for simplified development.

### UI Features

**Client**
- Login/connection window
- Authentication toggle (enable/disable username/password)
- QUIC head-of-line blocking toggle
- Remote window display and interaction

**Server**
- Setup and configuration window
- Authentication management
- Connection status display

## Development Roadmap

1. **Phase 1: Foundation**
   - [ ] Client login window UI
   - [ ] Server setup window UI
   - [ ] Server authentication and network code
   - [ ] Client authentication and network code

2. **Phase 2: Window Management**
   - [ ] Server-side window enumeration
   - [ ] Window metadata transmission (dimensions, titles)
   - [ ] Client-to-server window resize
   - [ ] Window close handling

3. **Phase 3: Input Handling**
   - [ ] Mouse movement replication (inspired by [JigglyMouser](https://github.com/LillyPK/Jiggly_Mouser))
   - [ ] Keyboard input forwarding
   - [ ] Window focus management

4. **Phase 4: Screen Capture**
   - [ ] Windows Graphics Capture API integration (reference: [Win32CaptureSample](https://github.com/robmikh/Win32CaptureSample))
   - [ ] Frame encoding and transmission
   - [ ] Client-side rendering
   - [ ] Dynamic title updates

## Build System

CMake-based build system for cross-component compilation and dependency management.

## Security Notes

- QUIC provides TLS 1.3 encryption by default
- Designed for **trusted local networks only**
- Optional authentication for access control
- Not intended for internet-facing deployments

## [License](https://github.com/LillyPK/ProtoXEF/blob/main/LICENSE)

## Contributing

Project is in early development. Feel free to open issues or submit pull requests.

---

*ProtoXEF - Remote Window Manager for your local network, built for performance.*
