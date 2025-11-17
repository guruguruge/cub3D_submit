#!/usr/bin/env bash
# Run VALID map tests only: builds, finds executable, runs valid maps, expects exit 0

BASE_DIR="$(cd "$(dirname "$0")/.." && pwd)"
MAP_DIR="$BASE_DIR/map"
LOG_DIR="$BASE_DIR/test_maps/logs_valid"
mkdir -p "$LOG_DIR"

# Build if Makefile present
if [ -f "$BASE_DIR/Makefile" ]; then
  echo "Makefile found: running make"
  (cd "$BASE_DIR" && make -s) || echo "make failed (continuing)"
fi

# find executable
candidates=(./cub3d ./cub3D ./a.out ./cub3d.out)
EXE=""
for p in "${candidates[@]}"; do
  if [ -x "$BASE_DIR/$p" ]; then EXE="$BASE_DIR/$p"; break; fi
done
if [ -z "$EXE" ]; then
  EXE=$(find "$BASE_DIR" -maxdepth 1 -type f -executable -print | xargs file -L 2>/dev/null | awk -F: '/ELF|executable/{print $1; exit}')
fi
if [ -z "$EXE" ]; then
  echo "Executable not found in project root. Please build and retry." >&2
  exit 2
fi
echo "Using executable: $EXE"

# VALID maps only
maps=(
  "map/valid_simple.cub"
  "map/valid_room.cub"
  "map/valid_donut.cub"
  "map/valid_header_mix.cub"
  "map/valid_header_newline_split.cub"
  "map/valid_tight_enclosed.cub"
  "map/valid_L_shaped.cub"
  "map/valid_narrow_corridor.cub"
  "map/valid_mixed_sizes.cub"
  "map/valid_border_tight.cub"
  "map/valid_max_dense.cub"
)

pass=0
fail=0
timeout_cmd="timeout 5s"

for mapfile in "${maps[@]}"; do
  fullmap="$BASE_DIR/$mapfile"
  logfile="$LOG_DIR/$(basename "$mapfile").log"
  printf "\n=== %s (expect: OK exit 0) ===\n" "$mapfile"
  if [ ! -f "$fullmap" ]; then
    echo "MAP NOT FOUND: $fullmap" | tee "$logfile"
    ((fail++)); continue
  fi
  # run with timeout, capture stdout+stderr
  $timeout_cmd "$EXE" "$fullmap" > "$logfile" 2>&1
  rc=$?
  # For valid maps, we expect exit 0
  if [ "$rc" -eq 0 ]; then
    echo "PASS (exit 0)" | tee -a "$logfile"
    ((pass++))
  else
    echo "FAIL (exit $rc) -- expected ok" | tee -a "$logfile"
    ((fail++))
  fi
done

echo
echo "SUMMARY: pass=$pass fail=$fail"
if [ "$fail" -ne 0 ]; then exit 1; fi
