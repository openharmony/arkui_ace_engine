/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once
#include <cstdint>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

#include "nia_ls.h"

namespace localsmt {

// ── Strength ────────────────────────────────────────────────────────────────

enum Strength {
    REQUIRED = 0,
    WEAK = 1,
    MEDIUM = 100,
    STRONG = 1000,
};

// ── Forward declarations ────────────────────────────────────────────────────

class Engine;
class Expr;
class Constraint;

class Expr {
public:
    struct Term {
        std::string varName;
        double coeff;
    };

    Expr() = default;
    explicit Expr(double c); // constant

    // Arithmetic
    Expr operator+(const Expr& o) const;
    Expr operator-(const Expr& o) const;
    Expr operator+(double s) const;
    Expr operator-(double s) const;
    Expr operator-() const;
    Expr operator*(double s) const;
    friend Expr operator*(double s, const Expr& e);
    friend Expr operator+(double c, const Expr& e);
    friend Expr operator-(double c, const Expr& e);

    // Comparison → Constraint
    Constraint operator<=(const Expr& rhs) const;
    Constraint operator>=(const Expr& rhs) const;
    Constraint operator==(const Expr& rhs) const;
    Constraint operator<(const Expr& rhs) const;
    Constraint operator>(const Expr& rhs) const;
    Constraint operator<=(double rhs) const;
    Constraint operator>=(double rhs) const;
    Constraint operator==(double rhs) const;
    Constraint operator<(double rhs) const;
    Constraint operator>(double rhs) const;

    /// Get solved value (only valid after Engine::solve)
    double Value() const;

    /// Variable name (empty if this is a complex expression)
    const std::string& Name() const;

private:
    friend class Engine;

    // Constructor for named variable (only Engine can create)
    Expr(const std::string& varName, Engine* engine);

    std::vector<Term> terms_;
    double constant_ = 0.0;
    Engine* engine_ = nullptr; // back-pointer for value()
    std::string primaryName_;  // set for simple variable exprs
};

// ── Constraint: result of comparing two Expr ────────────────────────────────

enum CompOp { LEQ, GEQ, EQ };

class Constraint {
public:
    Constraint() = default;

    Expr lhs;
    CompOp op = EQ;
    Expr rhs;

private:
    friend class Expr;
    Constraint(const Expr& l, CompOp o, const Expr& r);
};

// ── LitRef: handle returned by Engine::add() for use in clauses ─────────────

struct LitRef {
    int id = 0;
    LitRef operator-() const
    {
        return { -id };
    }
    operator int() const
    {
        return id;
    }
};

class Engine {
public:
    Engine();
    ~Engine();

    // ── Variables ──

    /// Create a variable expression (no bounds)
    Expr Var(const std::string& name);

    /// Create a variable expression with initial value (no bounds)
    Expr Var(const std::string& name, double initial);

    /// Create a variable expression with bounds
    Expr Var(const std::string& name, double lo, double hi);

    /// Create a variable expression with bounds and initial value
    Expr Var(const std::string& name, double lo, double hi, double initial);

    /// Set a inital value to a var. For bool var, 0 means false while 1 means true
    void SetInitVar(const std::string& name, double initialValue);

    // ── Constraints ──

    /// Add a constraint. Returns a literal handle for use in clauses.
    LitRef Add(const Constraint& c, int strength = REQUIRED);

    /// Add a disjunctive clause: at least one literal must hold.
    /// Use -lit for negation.
    void AddClause(const std::vector<LitRef>& lits);

    // ── Remove ──

    void RemoveConstraint(LitRef lit);

    // ── Solve ──

    bool Solve(int width = 0, int height = 0);
    bool Resolve(int width, int height);

    // ── Results ──

    struct VarResult {
        std::string name;
        double value;
    };

    std::vector<VarResult> GetResults() const;
    double GetVariable(const std::string& name) const;
    bool IsSolved() const
    {
        return solved_;
    }

    // ── Inspection ──

    /// Description of a constraint for debugging / inspection
    struct ConstraintDesc {
        int id;           // LitRef id
        std::string expr; // human-readable, e.g. "x + 2*y <= 100"
        int strength;     // REQUIRED / WEAK / MEDIUM / STRONG or custom
        bool removed;     // true if removeConstraint() was called
    };

    /// Return descriptions of all added constraints
    std::vector<ConstraintDesc> GetConstraints() const;

    /// Return descriptions of all added clauses (each clause is a list of literal ids)
    std::vector<std::vector<int>> GetClauses() const;

    /// Return all registered variable names
    std::vector<std::string> GetVariableNames() const;

    // ── Utility ──

    void Clear();

private:
    friend class Expr;

    struct ConstraintInfo {
        Expr lhs;
        CompOp op;
        Expr rhs;
        int strength;
        int litId;
        bool removed;
    };

    std::map<int, size_t> idToIdx_;
    std::vector<ConstraintInfo> constraints_;
    std::vector<std::vector<int>> clauses_;

    std::vector<std::string> varNames_;
    std::map<std::string, int> varIndex_;
    struct VarBound {
        double lo = -1e18;
        double hi = 1e18;
    };
    std::map<std::string, VarBound> varBounds_;
    std::map<std::string, double> varInitial_; // initial values for solver hint

    int nextId_ = 1;
    bool solved_ = false;
    bool dirty_ = true;

    std::vector<double> solution_;

    static std::string ExprToString(const Expr& e);
    bool BuildAndSolve(int width, int height);
    void EnsureVar(const std::string& name);

private:
    struct ActiveConstraint {
        size_t idx;
        int userId;
        int solverLitId;
    };
    struct BoundLit {
        std::string var;
        bool isLeq;
        RationNum bound;
        int solverLitId;
    };
    void CollectActiveConstraints(
        std::vector<ActiveConstraint>& active, std::vector<BoundLit>& boundLits, int& nextLit);
    void AllocateSolverLits(niaOverall::LsSolver& solver, const std::vector<ActiveConstraint>& active);
    void BuildConstraintLiterals(niaOverall::LsSolver& solver, const std::vector<ActiveConstraint>& active);
    void BuildBoundLiterals(niaOverall::LsSolver& solver, const std::vector<BoundLit>& boundLits);
    void BuildClauses(niaOverall::LsSolver& solver, const std::vector<ActiveConstraint>& active,
        const std::vector<BoundLit>& boundLits, std::map<int, int>& userToSolver);
    void FinalizeSolver(niaOverall::LsSolver& solver);
    bool SolveAndExtract(niaOverall::LsSolver& solver, int width, int height);
};

} // namespace localsmt
