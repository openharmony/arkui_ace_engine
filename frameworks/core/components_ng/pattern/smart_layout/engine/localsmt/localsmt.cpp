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

#include "localsmt.h"

#include <algorithm>
#include <cmath>
#include <set>
#include <sstream>

#include "../solver_src/sls_solver_overall/nia_ls.h"
#include "../solver_src/utils/ration_num.h"

namespace localsmt {

constexpr int32_t MAX_STEP = 50000;

constexpr int32_t CUT_OFF = 10;
// ─── Expr ───────────────────────────────────────────────────────────────────

Expr::Expr(double c) : constant_(c) {}

Expr::Expr(const std::string& varName, Engine* engine) : constant_(0.0), engine_(engine), primaryName_(varName)
{
    terms_.push_back({ varName, 1.0 });
}

Expr Expr::operator+(const Expr& o) const
{
    Expr r = *this;
    r.constant_ += o.constant_;
    r.primaryName_.clear(); // no longer a simple variable
    for (auto& t : o.terms_) {
        bool found = false;
        for (auto& rt : r.terms_) {
            if (rt.varName == t.varName) {
                rt.coeff += t.coeff;
                found = true;
                break;
            }
        }
        if (!found) {
            r.terms_.push_back(t);
        }
    }
    // propagate engine pointer
    if (!r.engine_) {
        r.engine_ = o.engine_;
    }
    return r;
}

Expr Expr::operator-(const Expr& o) const
{
    return *this + (-o);
}

Expr Expr::operator-() const
{
    return (*this) * (-1.0);
}

Expr Expr::operator+(double s) const
{
    return (*this) + Expr(s);
}

Expr Expr::operator-(double s) const
{
    return (*this) - Expr(s);
}

Expr Expr::operator*(double s) const
{
    Expr r;
    r.constant_ = constant_ * s;
    for (auto& t : terms_) {
        r.terms_.push_back({ t.varName, t.coeff * s });
    }
    r.engine_ = engine_;
    return r;
}

Expr operator*(double s, const Expr& e)
{
    return e * s;
}
Expr operator+(double c, const Expr& e)
{
    return Expr(c) + e;
}
Expr operator-(double c, const Expr& e)
{
    return Expr(c) - e;
}

// Comparison → Constraint
Constraint Expr::operator<=(const Expr& rhs) const
{
    return Constraint(*this, LEQ, rhs);
}
Constraint Expr::operator>=(const Expr& rhs) const
{
    return Constraint(*this, GEQ, rhs);
}
Constraint Expr::operator==(const Expr& rhs) const
{
    return Constraint(*this, EQ, rhs);
}
Constraint Expr::operator<(const Expr& rhs) const
{
    return Constraint(*this, LEQ, rhs);
}
Constraint Expr::operator>(const Expr& rhs) const
{
    return Constraint(*this, GEQ, rhs);
}
Constraint Expr::operator<=(double rhs) const
{
    return Constraint(*this, LEQ, Expr(rhs));
}
Constraint Expr::operator>=(double rhs) const
{
    return Constraint(*this, GEQ, Expr(rhs));
}
Constraint Expr::operator==(double rhs) const
{
    return Constraint(*this, EQ, Expr(rhs));
}
Constraint Expr::operator<(double rhs) const
{
    return Constraint(*this, LEQ, Expr(rhs));
}
Constraint Expr::operator>(double rhs) const
{
    return Constraint(*this, GEQ, Expr(rhs));
}

double Expr::Value() const
{
    if (!engine_) {
        std::cout << "Expr not bound to an engine";
        return 0;
    }
    if (primaryName_.empty()) {
        std::cout << "value() only works on simple variable Expr";
        return 0;
    }
    return engine_->GetVariable(primaryName_);
}

const std::string& Expr::Name() const
{
    return primaryName_;
}

// ─── Constraint ─────────────────────────────────────────────────────────────

Constraint::Constraint(const Expr& l, CompOp o, const Expr& r) : lhs(l), op(o), rhs(r) {}

// ─── Engine ─────────────────────────────────────────────────────────────────

Engine::Engine() {}
Engine::~Engine() {}

void Engine::EnsureVar(const std::string& name)
{
    if (varIndex_.find(name) == varIndex_.end()) {
        varIndex_[name] = static_cast<int>(varNames_.size());
        varNames_.push_back(name);
    }
}

Expr Engine::Var(const std::string& name)
{
    EnsureVar(name);
    return Expr(name, this);
}

Expr Engine::Var(const std::string& name, double initial)
{
    EnsureVar(name);
    varInitial_[name] = initial;
    return Expr(name, this);
}

Expr Engine::Var(const std::string& name, double lo, double hi)
{
    EnsureVar(name);
    varBounds_[name] = { lo, hi };
    return Expr(name, this);
}

Expr Engine::Var(const std::string& name, double lo, double hi, double initial)
{
    EnsureVar(name);
    varBounds_[name] = { lo, hi };
    varInitial_[name] = initial;
    return Expr(name, this);
}

void Engine::SetInitVar(const std::string& name, double initalValue)
{
    varInitial_[name] = initalValue;
}

LitRef Engine::Add(const Constraint& c, int strength)
{
    // Ensure all variables in lhs/rhs are registered
    for (auto& t : c.lhs.terms_) {
        EnsureVar(t.varName);
    }
    for (auto& t : c.rhs.terms_) {
        EnsureVar(t.varName);
    }

    int id = nextId_++;
    ConstraintInfo ci;
    ci.lhs = c.lhs;
    ci.op = c.op;
    ci.rhs = c.rhs;
    ci.strength = strength;
    ci.litId = id;
    ci.removed = false;

    idToIdx_[id] = constraints_.size();
    constraints_.push_back(ci);
    dirty_ = true;
    return { id };
}

void Engine::AddClause(const std::vector<LitRef>& lits)
{
    std::vector<int> ids;
    for (auto& l : lits) {
        ids.push_back(l.id);
    }
    clauses_.push_back(ids);
    dirty_ = true;
}

void Engine::RemoveConstraint(LitRef lit)
{
    auto it = idToIdx_.find(std::abs(lit.id));
    if (it != idToIdx_.end() && it->second < constraints_.size()) {
        constraints_[it->second].removed = true;
        dirty_ = true;
    }
}

// ─── Inspection ────────────────────────────────────────────────────────────

std::string Engine::ExprToString(const Expr& e)
{
    std::ostringstream os;
    bool first = true;
    for (auto& t : e.terms_) {
        if (t.coeff == 0) {
            continue;
        }
        if (!first) {
            if (t.coeff > 0) {
                os << " + ";
            } else {
                os << " - ";
            }
        } else if (t.coeff < 0) {
            os << "-";
        }
        first = false;
        double absC = std::abs(t.coeff);
        if (absC != 1.0) {
            os << absC << "*";
        }
        os << t.varName;
    }
    if (e.constant_ != 0 || first) {
        if (!first && e.constant_ > 0) {
            os << " + ";
        } else if (!first && e.constant_ < 0) {
            os << " - ";
        }
        if (!first && e.constant_ < 0) {
            os << std::abs(e.constant_);
        } else {
            os << e.constant_;
        }
    }
    return os.str();
}

std::vector<Engine::ConstraintDesc> Engine::GetConstraints() const
{
    std::vector<ConstraintDesc> result;
    result.reserve(constraints_.size());
    for (auto& ci : constraints_) {
        const char* opStr = "==";
        if (ci.op == LEQ) {
            opStr = "<=";
        } else if (ci.op == GEQ) {
            opStr = ">=";
        }

        std::ostringstream os;
        os << ExprToString(ci.lhs) << " " << opStr << " " << ExprToString(ci.rhs);

        result.push_back({ ci.litId, os.str(), ci.strength, ci.removed });
    }
    return result;
}

std::vector<std::vector<int>> Engine::GetClauses() const
{
    return clauses_;
}

std::vector<std::string> Engine::GetVariableNames() const
{
    return varNames_;
}

void Engine::Clear()
{
    constraints_.clear();
    clauses_.clear();
    idToIdx_.clear();
    varNames_.clear();
    varIndex_.clear();
    varBounds_.clear();
    varInitial_.clear();
    solution_.clear();
    nextId_ = 1;
    solved_ = false;
    dirty_ = true;
}

// ─── Direct Build & Solve ───────────────────────────────────────────────────

// Helper: normalize Expr to terms + constant (combine like terms)
struct NormExpr {
    struct Term {
        std::string var;
        RationNum coeff;
    };
    std::vector<Term> terms;
    RationNum constant;
};

// normalize is called from Engine::buildAndSolve (Engine is friend of Expr)
static NormExpr NormalizeExprs(const std::vector<Expr::Term>& lhsTerms, double lhsConst,
    const std::vector<Expr::Term>& rhsTerms, double rhsConst)
{
    NormExpr result;
    std::map<std::string, double> combined;
    for (auto& t : lhsTerms) {
        combined[t.varName] += t.coeff;
    }
    for (auto& t : rhsTerms) {
        combined[t.varName] -= t.coeff;
    }
    double c = lhsConst - rhsConst;

    for (auto& kv : combined) {
        RationNum rc = RationNum::FromDouble(kv.second);
        if (rc != 0) {
            result.terms.push_back({ kv.first, rc });
        }
    }
    result.constant = RationNum::FromDouble(c);
    return result;
}

bool Engine::BuildAndSolve(int width, int height)
{
    niaOverall::LsSolver solver(0, MAX_STEP, CUT_OFF, true);
    std::vector<ActiveConstraint> active;
    std::vector<BoundLit> boundLits;
    int nextLit = 1;

    CollectActiveConstraints(active, boundLits, nextLit);
    AllocateSolverLits(solver, active);
    BuildConstraintLiterals(solver, active);
    BuildBoundLiterals(solver, boundLits);

    std::map<int, int> userToSolver;
    BuildClauses(solver, active, boundLits, userToSolver);
    FinalizeSolver(solver);

    if (!SolveAndExtract(solver, width, height)) {
        return false;
    }

    solved_ = true;
    dirty_ = false;
    return true;
}

void Engine::CollectActiveConstraints(
    std::vector<ActiveConstraint>& active, std::vector<BoundLit>& boundLits, int& nextLit)
{
    for (size_t i = 0; i < constraints_.size(); i++) {
        if (constraints_[i].removed || constraints_[i].strength > 0) {
            continue;
        }
        active.push_back({ i, constraints_[i].litId, nextLit++ });
    }

    for (auto& kv : varBounds_) {
        if (kv.second.lo > -1e17) {
            boundLits.push_back({ kv.first, false, RationNum::FromDouble(kv.second.lo), nextLit++ });
        }
        if (kv.second.hi < 1e17) {
            boundLits.push_back({ kv.first, true, RationNum::FromDouble(kv.second.hi), nextLit++ });
        }
    }
}

void Engine::AllocateSolverLits(niaOverall::LsSolver& solver, const std::vector<ActiveConstraint>& active)
{
    int totalLits = 0;
    for (size_t i = 0; i < constraints_.size(); i++) {
        if (!constraints_[i].removed && constraints_[i].strength <= 0) {
            totalLits++;
        }
    }
    for (auto& kv : varBounds_) {
        if (kv.second.lo > -1e17)
            totalLits++;
        if (kv.second.hi < 1e17)
            totalLits++;
    }

    solver.MakeLitsSpace(totalLits + 1);
    solver._lits[0].litsIndex = 0;

    for (auto& name : varNames_) {
        solver.TransferNameToVar(name, true);
    }
    solver.TransferNameToVar(".w", true);
    solver.TransferNameToVar("BC_hight", true);
}

void Engine::BuildConstraintLiterals(niaOverall::LsSolver& solver, const std::vector<ActiveConstraint>& active)
{
    for (auto& ac : active) {
        auto& ci = constraints_[ac.idx];
        niaOverall::lit& l = solver._lits[ac.solverLitId];
        l.isNiaLit = true;
        l.litsIndex = ac.solverLitId;

        NormExpr ne = NormalizeExprs(ci.lhs.terms_, ci.lhs.constant_, ci.rhs.terms_, ci.rhs.constant_);

        for (auto& t : ne.terms) {
            uint64_t vi = solver.name2var[t.var];
            l.coffVars.push_back(niaOverall::CoffVar(static_cast<int>(vi), t.coeff));
        }

        switch (ci.op) {
            case LEQ:
                l.key = ne.constant;
                l.isEqual = false;
                break;
            case GEQ:
                for (auto& cv : l.coffVars) {
                    cv.coff = -cv.coff;
                }
                l.key = -ne.constant;
                l.isEqual = false;
                break;
            case EQ:
                l.key = ne.constant;
                l.isEqual = true;
                break;
        }
        solver.numOpt += l.coffVars.size();
    }
}

void Engine::BuildBoundLiterals(niaOverall::LsSolver& solver, const std::vector<BoundLit>& bound_lits)
{
    for (auto& bl : bound_lits) {
        niaOverall::lit& l = solver._lits[bl.solverLitId];
        l.isNiaLit = true;
        l.litsIndex = bl.solverLitId;
        uint64_t vi = solver.name2var[bl.var];

        if (bl.isLeq) {
            l.coffVars.push_back(niaOverall::CoffVar(static_cast<int>(vi), RationNum(1)));
            l.key = -bl.bound;
        } else {
            l.coffVars.push_back(niaOverall::CoffVar(static_cast<int>(vi), RationNum(-1)));
            l.key = bl.bound;
        }
        l.isEqual = false;
        solver.numOpt += 1;
    }
}

void Engine::BuildClauses(niaOverall::LsSolver& solver, const std::vector<ActiveConstraint>& active,
    const std::vector<BoundLit>& bound_lits, std::map<int, int>& user_to_solver)
{
    for (auto& ac : active) {
        user_to_solver[constraints_[ac.idx].litId] = ac.solverLitId;
    }

    std::set<int> in_user_clause;
    for (auto& cl : clauses_) {
        for (int uid : cl) {
            in_user_clause.insert(std::abs(uid));
        }
    }

    auto& ov = solver.originalVec;

    for (auto& ac : active) {
        if (!in_user_clause.count(constraints_[ac.idx].litId)) {
            ov.push_back({ ac.solverLitId });
        }
    }

    for (auto& cl : clauses_) {
        std::vector<int> solver_cl;
        for (int uid : cl) {
            int sign = (uid > 0) ? 1 : -1;
            auto it = user_to_solver.find(std::abs(uid));
            if (it != user_to_solver.end()) {
                solver_cl.push_back(sign * it->second);
            }
        }
        if (!solver_cl.empty()) {
            ov.push_back(solver_cl);
        }
    }

    for (auto& bl : bound_lits) {
        ov.push_back({ bl.solverLitId });
    }

    solver.DeleteRedundantClauses(ov);
}

void Engine::FinalizeSolver(niaOverall::LsSolver& solver)
{
    solver.basicComponentName = "BC";
    solver.bcWidthIdx = static_cast<int>(solver.name2var[".w"]);
    solver.bcHightIdx = static_cast<int>(solver.name2var["BC_hight"]);
    solver.numVars = static_cast<int>(solver._vars.size());
    solver.litAppear.resize(solver.numLits);
    solver.litsInCls = new Array(solver.numLits);
    solver.PrepareComponentsIdx();
    solver.RecordInfoAfterReadFile();
}

bool Engine::SolveAndExtract(niaOverall::LsSolver& solver, int width, int height)
{
    solver.BuildInstanceOriginal();
    if (solver.unsatInPreprocess) {
        solved_ = false;
        return false;
    }
    if (width > 0 || height > 0) {
        solver.BuildInstanceNewWidth(width, height);
        if (solver.unsatInPreprocess) {
            solved_ = false;
            return false;
        }
    }

    bool ok = solver.AssumeOneLiteral(varInitial_) || solver.LocalSearch(varInitial_);
    if (!ok) {
        solved_ = false;
        return false;
    }

    solution_.resize(varNames_.size(), 0.0);
    for (size_t i = 0; i < solver._vars.size() && i < solver._solution.size(); i++) {
        auto it = varIndex_.find(solver._vars[i].varName);
        if (it != varIndex_.end()) {
            solution_[it->second] = solver._solution[i].ToDouble();
        }
    }
    return true;
}

bool Engine::Solve(int width, int height)
{
    return BuildAndSolve(width, height);
}
bool Engine::Resolve(int width, int height)
{
    return BuildAndSolve(width, height);
}

std::vector<Engine::VarResult> Engine::GetResults() const
{
    std::vector<VarResult> results;
    if (!solved_) {
        return results;
    }
    for (size_t i = 0; i < varNames_.size(); i++) {
        results.push_back({ varNames_[i], solution_[i] });
    }
    return results;
}

double Engine::GetVariable(const std::string& name) const
{
    if (!solved_) {
        return 0.0;
    }
    auto it = varIndex_.find(name);
    if (it == varIndex_.end()) {
        return 0.0;
    }
    return solution_[it->second];
}

} // namespace localsmt
