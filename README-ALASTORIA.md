# Alastoria RME (Remere's Map Editor fork)

Fork of [hampusborgos/rme](https://github.com/hampusborgos/rme) for the Alastoria monorepo.

Upstream RME **flattens** TFS dynamic spawn pools (`<monsters chance="...">`) on save. This fork preserves them on load/save round-trip.

## What changed

| File | Change |
|------|--------|
| `source/spawn.h` | `SpawnMonsterPool` / `SpawnMonsterEntry` stored on `Spawn` |
| `source/spawn.cpp` | `deepCopy()` + `hasMonsterPoolAt()` |
| `source/iomap_otbm.cpp` | `loadSpawns` parses `<monsters>`; `saveSpawns` emits pools before flat `<monster>` |

TFS format (see `testserver/.../src/spawn.cpp`):

```xml
<spawn centerx="886" centery="1020" centerz="8" radius="8">
  <monsters x="-4" y="2" z="8" spawntime="60">
    <monster name="Duende [20]" chance="17" />
    <monster name="Duende [21]" chance="17" />
  </monsters>
</spawn>
```

Pools are **not** drawn as creatures on the map (no UI yet). They round-trip in spawn XML only.

## Build (Windows)

Requirements: **wxWidgets 3.x**, **Boost**, **CMake**, MSVC.

```powershell
powershell -NoProfile -File rme/scripts/build-windows.ps1
```

Output: `rme/build/Release/rme.exe` (path may vary by generator).

## Install + Alastoria creatures

```powershell
# 1) Build (or copy a prebuilt rme.exe into rme/build/Release/)
powershell -NoProfile -File rme/scripts/install-alastoria.ps1

# 2) Sync creature list from datapack (same as stock workflow)
powershell -NoProfile -File Map/rme/install-creatures.ps1
```

`install-alastoria.ps1` copies `rme.exe` to `%LOCALAPPDATA%\AlastoriaRME\` and sets HKCU registry keys for the custom 1098 data path (`Map/rme/data/1098/`).

## Workflow

1. Edit **only** `.otbm` in RME when possible; spawn XML is written beside the map.
2. With this fork, saving the map **keeps** dynamic pools in `*-spawn.xml`.
3. Copy `alastoria.otbm` + `alastoria-spawn.xml` to `testserver/forgottenserver - testserv/data/world/`.
4. Restart TFS (`/reload` does not reload spawns).

If you must use stock RME, run `.cursor/skills/ot-spawn-restore/scripts/restore-spawns.ps1` after every save.

## Remote

- Fork: https://github.com/AndreyMMP/rme
- Monorepo path: `OT/rme/`
