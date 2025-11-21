# Dynamic Color Placeholders

## Purpose
Certain UI components require colors derived dynamically from rendered content regions (e.g., dominant image color, readable contrasting text color over a background, accent extraction). To support this, the `Color` data structure can carry a *placeholder* handle instead of a concrete ARGB value. The render service resolves these placeholders to concrete colors. (Live push updates are out of current scope.)

## Scope (UI Layer)
We extend `Color` with:
- An enum `ColorPlaceholder` enumerating predefined dynamic sources.
- A lightweight `placeholder_` integral field (uint16_t) storing the placeholder kind (0 means none / concrete color).
- Factories & helpers: `explicit Color(ColorPlaceholder ph); bool IsPlaceholder() const; ColorPlaceholder GetPlaceholder() const;`
- Serialization additions: `ColorToString()` / `ToString()` will embed placeholder tag (e.g. `"#00000000|PH:DominantImage"`).
- Equality: placeholders compare by placeholder id & color space. If placeholder is active, `colorValue_` may keep an initial hint (e.g. fallback) but equality ignores hint's RGB unless both are non-placeholders.
- Backend contract: If `IsPlaceholder()` returns true, the backend should look up dynamic color generation routine by placeholder id.

## Data Flow
1. Developer adds .colorPicker modifier on any component with a specified ColorPlaceholder as the handle.
2. Modifier effect is propagated through UI to render server.
3. Render server posts periodic task to extract color from that component drawing layer and updates the local map (K: ColorPlaceholder, V: RGBA color) stored on this component node.
4. Developer uses that ColorPlaceholder on the same component or any of its child components.
5. When rendered, child component's drawing layer automatically picks up the mapped RGBA color to draw.

## Fallback Behavior
`colorValue_` for a placeholder is initialized to transparent.

## API Additions (Header)
```c++
class Color {
public:
    explicit Color(ColorPlaceholder ph);
    bool IsPlaceholder() const;
    ColorPlaceholder GetPlaceholder() const;
    void SetPlaceholder(ColorPlaceholder ph);
    bool HasConcreteValue() const; // !IsPlaceholder()
};
```

## String Representation
Placeholder values append a debug fragment: `#00000000|PH:<Name>` (e.g. `#00000000|PH:ContrastText`). Parsing the fragment back is not required today.

## Operator Semantics
Arithmetic on placeholders avoids undefined math:
- `+` returns the concrete side if one operand is a placeholder; if both are placeholders returns the left operand.
- `-`, `*`, `/` with a placeholder return the left operand unchanged.
This preserves chaining safety without producing misleading composite colors.

## Backend Integration Notes
Rendering service maps `ColorPlaceholder` to strategies; unknown ids default to transparent and should log. User-defined placeholders (>= `USER_DEFINED_START`) can later be registered by applications.

## Testing Strategy
Recommended unit tests:
1. `FromPlaceholder` sets `IsPlaceholder()` and correct placeholder id.
2. Equality: placeholders equal only if same placeholder id & color space.
3. Arithmetic operators match pass-through semantics.
4. `colorPicker()` JS API binds RSNode placeholder (verify `BindColorPicker` invoked).

## Migration & Compatibility
Existing code that inspects only raw 32-bit values remains unaffected (placeholders default to transparent). Prefer `IsPlaceholder()` before using raw value when contrast or blending logic matters.

## ArkTS Usage: colorPicker()
Use the chainable modifier `colorPicker(handle: ColorPlaceholder)` on any component to bind a dynamic color source to that component's render node.

Example:
```ts
Text('Hello').colorPicker(ColorPlaceholder.FOREGROUND); // or 'FOREGROUND'

// Use that placeholder elsewhere
Column().backgroundColor(ColorPlaceholder.FOREGROUND);
Text("Other").fontColor(ColorPlaceholder.FOREGROUND);
```

Internally this calls `RenderContext::BindColorPicker`, which forwards the placeholder id to `RSNode::BindColorPicker`. The backend then resolves and applies the actual color in its pipeline.

To clear a binding, pass `ColorPlaceholder.NONE`:
```ts
Text('Reset').colorPicker(ColorPlaceholder.NONE); // or 'NONE'
```