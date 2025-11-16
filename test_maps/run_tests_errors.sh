#!/usr/bin/env bash
# Run only error-case map tests: builds (if Makefile), finds executable, runs error maps, compares expected outcome.
BASE_DIR="$(cd "$(dirname "$0")/.." && pwd)"
MAP_DIR="$BASE_DIR/map"
LOG_DIR="$BASE_DIR/test_maps/logs_errors"
mkdir -p "$LOG_DIR"

# Build if Makefile present
if [ -f "$BASE_DIR/Makefile" ]; then
  echo "Makefile found: running make"
  (cd "$BASE_DIR" && make -s) || echo "make failed (continuing)"
fi

# find executable (common names) or first ELF executable
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

maps=(
  "map/invalid_open_wall.cub:err"
  "map/invalid_multiple_players.cub:err"
  "map/invalid_invalid_char.cub:err"
  "map/invalid_not_rectangular.cub:err"
  "map/invalid_missing_header.cub:err"
  "map/invalid_no_player.cub:err"
  "map/invalid_missing_texture.cub:err"
  "map/invalid_texture_extra_token.cub:err"
  "map/invalid_color_bad_value.cub:err"
  "map/invalid_duplicate_header.cub:err"
  "map/invalid_header_after_map.cub:err"
  "map/invalid_space_in_map.cub:err"
  "map/invalid_tab_in_map.cub:err"
  "map/invalid_trailing_space_line.cub:err"
  "map/invalid_empty_map.cub:err"
  "map/invalid_player_on_border.cub:err"
)

pass=0
fail=0
timeout_cmd="timeout 5s"

for me in "${maps[@]}"; do
  mapfile="${me%%:*}"
  expect="${me##*:}"
  fullmap="$BASE_DIR/$mapfile"
  logfile="$LOG_DIR/$(basename "$mapfile").log"
  printf "\n=== %s (expect: %s) ===\n" "$mapfile" "$expect"
  if [ ! -f "$fullmap" ]; then
    echo "MAP NOT FOUND: $fullmap" | tee "$logfile"
    ((fail++)); continue
  fi
  # run with timeout, capture stdout+stderr
  $timeout_cmd "$EXE" "$fullmap" > "$logfile" 2>&1
  rc=$?
  # rc==0 means success; non-zero means error/crash
  if [ "$expect" = "ok" ]; then
    if [ "$rc" -eq 0 ]; then
      echo "PASS (exit 0)" | tee -a "$logfile"
      ((pass++))
    else
      echo "FAIL (exit $rc) -- expected ok" | tee -a "$logfile"
      ((fail++))
    fi
  else
    if [ "$rc" -ne 0 ]; then
      echo "PASS (exit $rc) -- expected err" | tee -a "$logfile"
      ((pass++))
    else
      echo "FAIL (exit 0) -- expected err" | tee -a "$logfile"
      ((fail++))
    fi
  fi
done

echo
echo "SUMMARY: pass=$pass fail=$fail"
if [ "$fail" -ne 0 ]; then exit 1; fi
