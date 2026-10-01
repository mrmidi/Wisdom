# Fork CI for examples decoupling

These files are personal CI for `mrmidi/Wisdom`; keep them out of upstream contributions.
The separate worktree contains the current examples-decoupling changes for now plus these CI additions.

Both workflows run on pushes to every branch, excluding tags. GitHub reads workflows from the pushed branch: that branch must contain the workflow files. The repository conditions restrict jobs to this fork.

- `ci.yml` preserves the existing four builds: Windows DX12, Windows Vulkan, Windows Clang/Vulkan, and Linux Vulkan, including examples. Its fork-only changes broaden the push filter and add repository conditions.
- `personal-ci.yml` adds Windows DX12 and Linux Vulkan builds with examples and tests disabled, and the generator independently enabled. It installs Wisdom and compiles/links C99 static/shared consumers and C++ static/shared/header-only consumers using the exported package. Package configuration must preserve the consumer's DXC setting and must not expose examples' shader helpers.
- The macOS job configures the library tree but builds only the independent generator, then runs `--help`. It does not regenerate source files. Full library builds on macOS are not supported by this upstream base.

The old and new workflows use the same pushed source revision. This compares existing example builds with the additional decoupling checks; it does not automatically build an earlier upstream revision as a baseline.

Consumers are built, not executed. There are no GPU correctness or performance claims. Runner GPU probing and instrumentation belong to later foundation work.

Personal jobs use the runner default timeout, keep other matrix entries running after a failure, and upload logs and CMake diagnostics for seven days. Manual dispatch of Personal CI requires the workflow to exist on the fork's default branch first.

Local validation: actionlint passes for both workflows; the C99 consumer passes a syntax check against installed public headers; the macOS generator build and `--help` pass using the installed Vulkan headers. The first GitHub run at `a48beaf` passed all seven jobs across the existing and personal workflows, including Windows/Linux installed consumers. Later local changes require another authorized push before those results apply to them.
