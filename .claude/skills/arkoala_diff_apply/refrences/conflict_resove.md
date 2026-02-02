# Conflict Resolution Guide

Detailed patterns for resolving diff conflicts in ace_engine (TypeScript/C++ hybrid).

## General Principles

1. **Original logic is sacred** — When in doubt, preserve it
2. **Additive over destructive** — Prefer adding new code alongside old rather than replacing
3. **Context matters** — A 3-line context mismatch usually means the file changed; find the new location
4. **Test incrementally** — Resolve one conflict, compile, repeat

## Understanding .rej Files

A `.rej` file shows what `patch` couldn't apply:

```diff
--- a/file.cpp
+++ b/file.cpp
@@ -10,7 +10,7 @@
 void foo() {
-    oldCode();
+    newCode();
 }
```

This means: at line 10, expected `oldCode()` but didn't find it.

## C++ Conflict Patterns

### Pattern 1: Function Signature Changed

**Reject:**
```diff
-void ProcessData(int value) {
+void ProcessData(int value, bool validate) {
```

**Original file now has:**
```cpp
void ProcessData(int value, const std::string& name) {
```

**Resolution:** Merge both changes:
```cpp
void ProcessData(int value, const std::string& name, bool validate) {
```

### Pattern 2: Include Order Conflicts

**Reject:**
```diff
 #include "base.h"
+#include "new_feature.h"
 #include "utils.h"
```

**Resolution:** Find appropriate location, respect grouping:
```cpp
#include "base.h"
#include "new_feature.h"  // Add here, maintain alphabetical if project uses it
#include "utils.h"
```

### Pattern 3: Memory Management Changes

**CRITICAL — Never break RAII patterns**

**Reject wants:**
```diff
-auto ptr = std::make_unique<Foo>();
+Foo* ptr = new Foo();
```

**Resolution:** Keep the smart pointer, adapt the new logic:
```cpp
auto ptr = std::make_unique<Foo>();
// Adapt whatever the diff intended to do with raw pointer
```

### Pattern 4: Namespace/Class Scope Shift

**Reject:**
```diff
 void MyClass::Method() {
+    newStatement();
 }
```

**But method moved to different line or class restructured.**

**Resolution:**
1. Search for `MyClass::Method` in current file
2. Find the actual current location
3. Apply the change there

## TypeScript/ETS Conflict Patterns

### Pattern 1: Import Conflicts

**Reject:**
```diff
 import { ComponentA } from './components';
+import { NewUtil } from './utils';
 import { ServiceB } from './services';
```

**Resolution:** Add import in appropriate section:
```typescript
import { ComponentA } from './components';
import { ServiceB } from './services';
import { NewUtil } from './utils';  // Group with other utils or alphabetize
```

### Pattern 2: Interface Extension

**Reject:**
```diff
 interface Config {
   name: string;
+  newField: number;
 }
```

**Current file has additional fields:**
```typescript
interface Config {
  name: string;
  addedField: boolean;  // Someone else added this
}
```

**Resolution:**
```typescript
interface Config {
  name: string;
  addedField: boolean;
  newField: number;  // Add the new field
}
```

### Pattern 3: Async/Await Modifications

**CRITICAL — Preserve async boundaries**

**Reject wants to add sync call inside async function:**
```diff
 async function loadData() {
+  processSync(data);  // This might be okay
   return await fetchData();
 }
```

**Check:** Does `processSync` need to be awaited? If the diff's intent was async, fix it:
```typescript
async function loadData() {
  await processAsync(data);  // If it should be async
  return await fetchData();
}
```

### Pattern 4: Decorator Changes (ETS)

**Reject:**
```diff
 @Component
+@Preview
 struct MyComponent {
```

**Resolution:** Add decorator in correct order (check project conventions):
```typescript
@Preview  // Usually preview decorators come first
@Component
struct MyComponent {
```

## Conflict Resolution Workflow

```
For each .rej file:
│
├─ Read the rejected hunk
│
├─ Locate target in actual file
│  └─ Search for unique strings from context lines
│
├─ Understand the intent
│  ├─ Adding new code? → Find right insertion point
│  ├─ Modifying existing? → Find current version, merge
│  └─ Deleting code? → Verify it's safe to delete
│
├─ Apply change manually
│  └─ Preserve original error handling, types, memory patterns
│
├─ Delete the .rej file
│
└─ Compile to verify
```

## When to Ask for Human Review

Mark for human review (add `// TODO: REVIEW` comment) when:

- Diff deletes error handling code
- Diff changes public API signatures
- Diff modifies security-sensitive code (auth, crypto, permissions)
- You can't determine the intent of the change
- Multiple valid interpretations exist

## Quick Conflict Commands

```bash
# Find all rejects
find . -name "*.rej"

# Show reject content
cat path/to/file.rej

# After resolving, clean up
find . -name "*.rej" -delete

# Verify no rejects remain
find . -name "*.rej" | wc -l  # Should be 0
```