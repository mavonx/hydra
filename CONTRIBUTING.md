# Contributing to hydra

Thank you for your interest in contributing to **hydra**! We welcome bug reports, feature suggestions, documentation improvements, and code contributions.

## Code of Conduct

This project and everyone participating in it is governed by our [Code of Conduct](CODE_OF_CONDUCT.md). By participating, you are expected to uphold it.

## How Can I Contribute?

### Reporting Bugs

Before opening a new issue, check existing [issues](https://github.com/mavonx/hydra/issues) to avoid duplicates.

### Suggesting Features

Feature suggestions are welcome; please describe the problem you are trying to solve rather than just the proposed solution, provide a concrete example of the expected command and output, and detail any alternative approaches you considered.

### Improving Documentation

Fixing typos, clarifying confusing sections, or adding examples is always a welcome, low-friction way to contribute.

### Submitting Code

Look for issues labeled `good first issue` for a good place to start. If you'd like to work on something, leave a comment on the issue first so effort isn't duplicated.

## Development Setup

### Prerequisites

- CMake (v3.28 or higher)
- A C++ compiler with full C++20 support (GCC 10+, Clang 10+, or MSVC 2019+)

### Getting Started

1. Fork the repository on GitHub.
2. Clone your fork locally using `git clone https://github.com/YOUR_USERNAME/hydra.git`.
3. Configure the build using `cmake -B build`.
4. Build the project using `cmake --build build`.
5. Run the test suite using `ctest --output-on-failure` to confirm your setup works.

## Submitting a Pull Request

1. Create a feature branch from `main` using the format `type/issue-number` (e.g., `feat/issue-4` or `fix/issue-12`).
2. Commit your changes locally following the [Commit Message Convention](#commit-message-convention).
3. Push your branch to your fork using `git push origin type/issue-number`.
4. Open a Pull Request against the `main` branch.
5. Reference the relevant issue in your PR description (e.g., `Closes #4`).

## Commit Message Convention

```txt
type(scope): short description
```

- Common Types:
    - `feat`: Adding, adjusting, or removing a feature.
    - `fix`: Fixing a bug in a preceding `feat`.
    - `refactor`: Rewriting or restructuring code without changing behavior.
    - `perf`: A `refactor` specifically aimed at improving performance.
    - `style`: Code style only (whitespace, formatting, missing semicolons) with no behavior change.
    - `test`: Adding missing tests or correcting existing ones.
    - `docs`: Documentation-only changes.
    - `build`: Build tools, dependencies, or CMake configuration changes.
    - `ops`: CI/CD, infrastructure, deployment, or monitoring updates.
    - `chore`: Maintenance tasks (e.g., `.gitignore` updates, initial setup).

**Scope** is optional and gives extra context (e.g., `feat(parser): ...`). Do not use issue numbers as scopes.
