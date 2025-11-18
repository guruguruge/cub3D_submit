# cub3D - Raycasting 3D Game Engine

A raycasting-based 3D game engine written in C using MinilibX, inspired by Wolfenstein 3D.

## Build

```bash
make
```

Generates executable: `cub3D`

## Run

```bash
./cub3D <path_to_map.cub>
```

Example:
```bash
./cub3D map/valid_simple.cub
```

## Test

### Automated Testing

The project includes comprehensive automated test suites for both valid and invalid map files.

#### Valid Map Tests

Run all **valid** map tests (expecting exit code 0):

```bash
bash test_maps/run_tests_valid.sh
```

This tests 11 valid map configurations including:
- Simple rectangular maps
- Donut-shaped (enclosed inner space)
- L-shaped corridors
- Non-rectangular (variable line length) maps
- Dense maze-like structures

#### Invalid Map Tests

Run all **invalid** map tests (expecting non-zero exit code):

```bash
bash test_maps/run_tests_errors.sh
```

This tests 16 error cases including:
- Missing headers (NO/SO/WE/EA/C/F)
- Duplicate headers
- Missing or invalid textures
- Invalid map characters
- Map structure issues (not enclosed, no player, multiple players)
- Malformed input (tabs, trailing spaces)

### Manual Testing

Test individual maps:

```bash
./cub3D map/valid_simple.cub       # Should succeed
./cub3D map/invalid_open_wall.cub  # Should fail with error message
```

### Test Results

All tests should pass:
- **Valid tests**: ✅ 11/11 PASS
- **Error tests**: ✅ 16/16 PASS

Test logs are saved to:
- `test_maps/logs_valid/` - Valid map test logs
- `test_maps/logs_errors/` - Invalid map test logs

## Features

### Parsing & Validation
- Header validation (NO/SO/WE/EA/C/F presence and duplicates)
- RGB color validation (0-255 range, 3 components)
- Texture file validation (.xpm extension, file existence)
- Map structure validation:
  - Character set validation (0, 1, space, N/S/E/W)
  - Player count validation (exactly 1)
  - Wall enclosure validation (four-direction check)
  - Non-rectangular map support (auto-padding)

### Rendering
- DDA raycasting algorithm
- Wall texture mapping
- Per-perpendicular distance rendering
- Optimized frame buffer reuse
- FPS limiting (30 FPS) without sleep functions

### Player Movement
- WASD keys for movement (5 units per step)
- Arrow keys for rotation (90° per step)
- Real-time camera updates

## Test Map Locations

### Valid Maps (`map/valid_*.cub`)
- `valid_simple.cub` - Basic 7x5 rectangular map
- `valid_room.cub` - Medium-sized room
- `valid_donut.cub` - Donut shape (enclosed interior)
- `valid_header_mix.cub` - Mixed header order
- `valid_header_newline_split.cub` - Headers split by newlines
- `valid_tight_enclosed.cub` - Minimal 6x5 enclosure
- `valid_L_shaped.cub` - L-shaped corridor
- `valid_narrow_corridor.cub` - Tight hallway (2 units wide)
- `valid_mixed_sizes.cub` - Non-rectangular (variable line lengths)
- `valid_border_tight.cub` - Player positioned near boundary
- `valid_max_dense.cub` - Complex maze (23x10)

### Invalid Maps (`map/invalid_*.cub`)
- `invalid_open_wall.cub` - Map not fully enclosed
- `invalid_multiple_players.cub` - More than one player
- `invalid_no_player.cub` - No player spawn
- `invalid_invalid_char.cub` - Invalid character in map (e.g., 'X')
- `invalid_not_rectangular.cub` - Inconsistent row lengths
- `invalid_missing_header.cub` - Missing required headers
- `invalid_missing_texture.cub` - Texture file not found
- `invalid_texture_extra_token.cub` - Extra tokens after texture path
- `invalid_color_bad_value.cub` - RGB values out of range
- `invalid_duplicate_header.cub` - Duplicate header identifiers
- `invalid_header_after_map.cub` - Header after map section
- `invalid_space_in_map.cub` - Invalid spacing in map
- `invalid_tab_in_map.cub` - Tab character in map
- `invalid_trailing_space_line.cub` - Trailing spaces on map lines
- `invalid_empty_map.cub` - Empty map section
- `invalid_player_on_border.cub` - Player on map boundary

## Key Optimizations

1. **Frame Buffer Reuse** - Avoid malloc/free per frame
2. **Lookup Tables** - Pre-computed sine/cosine/atan values
3. **FPS Limiting** - Time-based (gettimeofday) without sleep calls
4. **DDA Algorithm** - Efficient wall intersection detection
5. **Perpendicular Distance** - Avoids fisheye distortion

## Notes

- Map line lengths can vary (non-rectangular); the engine auto-pads with spaces
- Wall enclosure checked via four-direction validation (top/bottom/left/right)
- Textures must be 64x64 .xpm files
- RGB colors use standard 0-255 range

## Build Info

Compiled with: `-Wall -Wextra -Werror`
Libraries: MinilibX Linux, libm
