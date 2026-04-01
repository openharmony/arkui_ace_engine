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

#include "nia_ls.h"
namespace niaOverall {

// initialize
LsSolver::LsSolver()
    : maxStep(UINT64_MAX), cutoff(CUT_OFF), additionalLen(ADDITIONAL_LEN), completeLs(false),
      smoothProbability(SMOO_PROBABILITY), swtThreshold(SWT_THRESHOLD), swtP(K_DEFAULT_SWT_P)

{
    mt.seed(1);
}

LsSolver::LsSolver(int randomSeed, uint64_t maxStep, double cutoff, bool completeLs)
    : maxStep(maxStep), cutoff(cutoff), additionalLen(ADDITIONAL_LEN), completeLs(completeLs),
      smoothProbability(SMOO_PROBABILITY), swtThreshold(SWT_THRESHOLD), swtP(K_DEFAULT_SWT_P)
{
    mt.seed(randomSeed);
}

void LsSolver::Initialize(const std::map<std::string, double>& varInitial)
{
    PrepareClsLitIdxForVars();
    SetPreValue();
    ClearPrevData();
    ConstructSolution(varInitial);
    InitializeClauseDatas();
    InitializeVariableDatas();
    bestFoundThisRestart = unsatClauses->GetSize();
    UpdateBestSolution();
}
void LsSolver::ClearPrevData()
{
    for (int v : boolVarVec) {
        _vars[v].score = 0;
    }
    bestFoundHardCostThisBool = INT32_MAX;
    bestFoundHardCostThisNia = INT32_MAX;
    noImproveCntBool = 0;
    noImproveCntNia = 0;
    unsatClauses->Clear();
    std::fill(tabulist.begin(), tabulist.end(), 0);
    std::fill(_litMakeBreak.begin(), _litMakeBreak.end(), 0);
    std::fill(isInUnsatClause.begin(), isInUnsatClause.end(), false);
    std::fill(lastMove.begin(), lastMove.end(), 0);
    std::fill(isChosenBoolVar.begin(), isChosenBoolVar.end(), false);
    falseLitOccur->Clear();
}

// construction
void LsSolver::ConstructSolution(const std::map<std::string, double>& varInitial)
{
    std::vector<double> initValues(numVars, 0);
    for (auto& name2Value : varInitial) {
        auto it = name2var.find(name2Value.first);
        if (it != name2var.end() && it->second < initValues.size()) {
            initValues[it->second] = name2Value.second;
        }
    }
    for (int i = 0; i < numVars; i++) {
        RationNum varValue = (_vars[i].isNia) ? RationNum::FromDouble(initValues[i]) :
            (initValues[i] < 0.5 ? RationNum(-1) : RationNum(1));
        if (!_vars[i].isNia) {
            if (upValueVars[i] != 0) {
                _solution[i] = upValueVars[i];
            } else {
                _solution[i] = varValue;
            }
            continue;
        }
        if (_vars[i].lowBound > varValue) {
            _solution[i] = _vars[i].lowBound;
        } else if (_vars[i].upper_bound < varValue) {
            _solution[i] = _vars[i].upper_bound;
        } else {
            _solution[i] = varValue;
        }
    }
    InitializeLitDatas();
}

void LsSolver::ReadModel()
{
    int size;
    std::cin >> size;
    std::string inString;
    std::string inString2;
    for (int i = 0; i < size; i++) {
        std::cin >> inString;
        std::cin >> inString2;
        if (name2var.find(inString) != name2var.end()) {
            if (inString2 == "false") {
                _solution[name2var[inString]] = -1;
            } else if (inString2 == "true") {
                _solution[name2var[inString]] = 1;
            } else {
                _solution[name2var[inString]] = atoi(inString2.c_str());
            }
        }
    }
}

void LsSolver::InitializeVariableDatas() {}

// initialize the delta of each literal by DeltaLit operation
void LsSolver::InitializeLitDatas()
{
    for (lit& l : _lits) {
        if (l.isNiaLit) {
            if (l.litsIndex == 0) {
                l.isTrue = true;
                continue;
            }
            l.delta = DeltaLit(l);
            l.isTrue = l.isEqual ? (l.delta == 0 ? 1 : -1) : (l.delta <= 0 ? 1 : -1);
            continue; // even when a nia lit is not appeared, it can still be determined
        } else {
            if (l.litsIndex != 0 && litAppear[l.litsIndex]) {
                l.isTrue = (_solution[l.delta.ToInt()] > 0) ? 1 : -1;
            } else {
                l.isTrue = 1;
            } // the boolean lit does not appear, assuming it is true
        }
    }
}
// set the sat num of each clause, and sat/unsat a clause
void LsSolver::InitializeClauseDatas()
{
    litInUnsatClauseNum = 0;
    boolLitInUnsatClauseNum = 0;
    for (uint64_t c = 0; c < numClauses; c++) {
        clause* cl = &(_clauses[c]);
        cl->satCount = 0;
        cl->weight = 1;
        for (int lIdx : cl->literals) {
            if (lIdx * _lits[std::abs(lIdx)].isTrue > 0) {
                cl->satCount++;
                cl->watchLitIdx = lIdx;
            } // determine the sat count and watch lit
        }
        if (cl->satCount == 0) {
            UnsatAClause(c);
            litInUnsatClauseNum += _clauses[c].literals.size();
            boolLitInUnsatClauseNum += _clauses[c].boolLiterals.size();
            for (int lSignIdx : cl->boolLiterals) {
                _vars[_lits[std::abs(lSignIdx)].delta.ToInt()].score++;
            }
        } else {
            SatAClause(c);
        }
        if (cl->satCount > 0 && cl->satCount < cl->literals.size()) {
            satClauseWithFalseLiteral->InsertElement((int)c);
        }
        if (cl->satCount == 1) {
            lit* l = &(_lits[std::abs(cl->watchLitIdx)]);
            if (!l->isNiaLit) {
                _vars[l->delta.ToInt()].score--;
            }
        }
    }
    totalClauseWeight = numClauses;
}

} // namespace niaOverall
