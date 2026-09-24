mathlib

A mathematical library for Python, developed to provide reusable mathematical tools while implementing mathematical logic directly in Python.

Version

v1.0.2

Overview

mathlib is a Python mathematics project that organizes mathematical functions, calculations, and object-oriented structures into reusable modules.

The library covers several mathematical areas, including:

Probability
Statistics
Combinatorics
Mathematical functions
Plane geometry
Analytic geometry
Spatial geometry

The project combines mathematical study with practical software development, allowing mathematical concepts to be transformed into reusable Python code.

Installation

The package is available on PyPI as:

advancedmath-natcar2000

Install it with:

pip install advancedmath-natcar2000
Requirements
Python 3.10 or newer
License

This project is licensed under the GPL.

Modules

The library is organized into independent mathematical modules.

Probability

The probability module provides functions for common probability operations, including:

Basic probability
Complementary probability
Conditional probability
Joint probability
Union of events
Statistics

The statistic module provides functionality for statistical calculations and analysis.

Combinatorics

The combinatorics module provides tools for combinatorial calculations.

Functions

The function module contains functionality related to mathematical functions.

Plane Geometry

The plan_geometry module provides structures and calculations related to plane geometry.

Analytic Geometry

The analytic_geometry module provides functionality for analytical geometry.

Spatial Geometry

The spatial_geometry module provides structures and calculations for three-dimensional geometry.

Mathematical Constants

The library defines its own mathematical constants, including:

PI = 3.141592653589793
EULER = 2.718281828459045

The core mathematical implementations were designed without directly depending on Python's math module.

Object-Oriented Geometry

Geometry-related functionality uses object-oriented structures where appropriate.

This allows geometric objects to encapsulate their properties and calculations, providing a modular foundation for future extensions.

Input Validation

The library includes validation helpers for mathematical inputs.

Examples include:

validate_values
validate_coefficient

These helpers are used to validate values and coefficients before performing calculations.

Design Goals

The main goals of mathlib are:

Provide reusable mathematical functionality.
Translate mathematical reasoning into practical Python code.
Keep mathematical implementations understandable.
Organize mathematical domains into independent modules.
Practice software engineering through the development of a real Python package.
Minimize unnecessary dependencies for core mathematical operations.
Provide a foundation for future mathematical functionality.
Example

A typical usage pattern is:

from advancedmath import probability

result = probability(...)
print(result)

The available functions depend on the mathematical module being used.

Project Structure

A simplified representation of the project structure:

mathlib/
│
├── analytic_geometry/
├── combinatorics/
├── function/
├── plan_geometry/
├── probability/
├── spatial_geometry/
├── statistic/
│
├── pyproject.toml
└── README.md
Development

mathlib is developed in Python using a modular architecture.

Each mathematical domain is organized separately, making it possible to add new functions and concepts without unnecessarily affecting other parts of the library.

The project is also continuously evolving as new mathematical concepts and software engineering techniques are studied and implemented.

Current Release

v1.0.2

The project has progressed through multiple releases, with 1.0.2 being the current version.

Project Objective

mathlib was created to combine mathematics, programming, and software development in a single practical project.

Instead of treating mathematics only as a collection of formulas, the project focuses on transforming mathematical reasoning into reusable software.

The long-term goal is to expand the library with additional mathematical domains, algorithms, functions, and computational tools.

mathlib v1.0.2

Developed by Natanael Rodrigues
