#!/usr/bin/env bash
# Run INVALID map tests only: builds, finds executable, runs invalid maps, expects non-zero exit

BASE_DIR="$(cd "$(dirname "$0")/.." && pwd)"
MAP_DIR="$BASE_DIR/map"
LOG_DIR="$BASE_DIR/test_maps/logs_errors"
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

# INVALID maps only
maps=(
  "map/invalid_open_wall.cub"
  "map/invalid_multiple_players.cub"
  "map/invalid_invalid_char.cub"
  "map/invalid_not_rectangular.cub"
  "map/invalid_missing_header.cub"
  "map/invalid_no_player.cub"
  "map/invalid_missing_texture.cub"
  "map/invalid_texture_extra_token.cub"
  "map/invalid_color_bad_value.cub"
  "map/invalid_duplicate_header.cub"
  "map/invalid_header_after_map.cub"
  "map/invalid_space_in_map.cub"
  "map/invalid_tab_in_map.cub"
  "map/invalid_trailing_space_line.cub"
  "map/invalid_empty_map.cub"
  "map/invalid_player_on_border.cub"
  "map/invalid_header_mimic.cub"
)

pass=0
fail=0
timeout_cmd="timeout 5s"

for mapfile in "${maps[@]}"; do
  fullmap="$BASE_DIR/$mapfile"
  logfile="$LOG_DIR/$(basename "$mapfile").log"
  printf "\n=== %s (expect: ERR non-zero) ===\n" "$mapfile"
  if [ ! -f "$fullmap" ]; then
    echo "MAP NOT FOUND: $fullmap" | tee "$logfile"
    ((fail++)); continue
  fi
  # run with timeout, capture stdout+stderr
  $timeout_cmd "$EXE" "$fullmap" > "$logfile" 2>&1
  rc=$?
  # For invalid maps, we expect non-zero exit
  if [ "$rc" -ne 0 ]; then
    echo "PASS (exit $rc) -- expected err" | tee -a "$logfile"
    ((pass++))
  else
    echo "FAIL (exit 0) -- expected err" | tee -a "$logfile"
    ((fail++))
  fi
done

echo
echo "SUMMARY: pass=$pass fail=$fail"
if [ "$fail" -ne 0 ]; then exit 1; fi
