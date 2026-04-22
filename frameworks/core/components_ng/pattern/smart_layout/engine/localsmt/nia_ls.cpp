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

#include <sstream>
#define LS_DEBUG
namespace niaOverall {

// random walk
void LsSolver::UpdateClauseWeight()
{
    for (int i = 0; i < unsatClauses->GetSize(); i++) {
        Clause* unsatCl = &(clauses[unsatClauses->GetElementByIndex(i)]);
        unsatCl->weight++;
        for (int lSignIdx : unsatCl->boolLiterals) {
            vars[lits[std::abs(lSignIdx)].delta.ToInt()].score++;
        }
    }
    totalClauseWeight += unsatClauses->GetSize();
}

void LsSolver::SmoothClauseWeight()
{
    for (int i = 0; i < numClauses; i++) {
        if (clauses[i].weight > 1 && !unsatClauses->IsInArray(i)) {
            clauses[i].weight--;
            totalClauseWeight--;
            if (clauses[i].satCount == 1 && !lits[std::abs(clauses[i].watchLitIdx)].isNiaLit) {
                int64_t watchLitIdx = lits[std::abs(clauses[i].watchLitIdx)].delta.ToInt();
                vars[watchLitIdx].score++;
            }
        }
    }
}

// when there is no operation, simply find a lit in a random false clause, pick a random var with coff!=0, set it to 0
void LsSolver::NoOperationRandomWalk()
{
    Clause* cp =
        &(clauses[unsatClauses->GetElementByIndex(mt() % unsatClauses->GetSize())]); // choose a random unsat clause
    int litIdx = cp->literals[mt() % cp->literals.size()];
    Lit* l = &(lits[std::abs(litIdx)]);
    if (!l->isNiaLit) {
        CriticalMove(l->delta.ToInt(), RationNum(0));
        return;
    } // boolean lit
    size_t numCv = l->coffVars.size();
    if (numCv == 0) {
        return;
    }
    int varIdxCurr = l->coffVars[mt() % numCv].varIdx;
    if (varIdxCurr == unchangedVar1 || varIdxCurr == unchangedVar2) {
        return;
    }
    RationNum futureSolution = RationNum(0);
    Variable* var = &(vars[varIdxCurr]);
    if (var->lowBound > 0) {
        futureSolution = var->lowBound;
    } else if (var->upperBound < 0) {
        futureSolution = var->upperBound;
    }
    CriticalMove(varIdxCurr, futureSolution - solution[varIdxCurr]); // move a random var with coff!=0 to 0
}

void LsSolver::RandomWalk()
{
    int operationIdx(0);
    int operationIdxBool(0);
    int clauseIdx;
    Clause* cp;
    // determine the operations
    for (int i = 0; i < K_RAND_WALK_ITER && operationIdx + operationIdxBool < K_RAND_WALK_MAX_OPS; i++) {
        clauseIdx = unsatClauses->GetElementByIndex(mt() % unsatClauses->GetSize());
        cp = &(clauses[clauseIdx]);
        for (int lIdx : cp->niaLiterals) {
            AddOperationFromFalseLit(false, lIdx, operationIdx);
        }
        for (int lIdx : cp->boolLiterals) {
            AddBoolOperation(false, lIdx, operationIdxBool);
        }
    }
    for (int i = 0; i < operationIdxBool; i++) {
        isChosenBoolVar[operationVarIdxBoolVec[i]] = false; // recover bool vec
    }
    falseLitOccur->Clear(); // recover the falseLit
    if (operationIdx + operationIdxBool == 0) {
        lastOpVar = UINT64_MAX; // in case the random walk make no move, it will not ban the only operation
        NoOperationRandomWalk();
        return; // if no operation, return
    }
    // nia mode make move
    if (operationIdxBool == 0 || (operationIdx > 0 && operationIdxBool > 0 && !isInBoolSearch)) {
        RationNum bestValueNia;
        int bestVarIdxNia;
        int bestScoreNia = INT32_MIN;
        SelectBestOperationFromVec(
            operationIdx, bestScoreNia, bestVarIdxNia, bestValueNia); // choose best nia operation
        CriticalMove(bestVarIdxNia, bestValueNia);
    } else {
        int bestVarIdxBool = 0; // bool mode make move choose best bool operation
        int bestScoreBool = INT32_MIN;
        SelectBestOperationFromBoolVec(operationIdxBool, bestScoreBool, bestVarIdxBool);
        CriticalMove(bestVarIdxBool, RationNum(0));
    }
}

// basic operations
bool LsSolver::UpdateBestSolution()
{
    bool improve = false;
    if (unsatClauses->GetSize() < bestFoundThisRestart) {
        improve = true;
        bestFoundThisRestart = unsatClauses->GetSize();
    }
    if (unsatClauses->GetSize() < bestFoundCost) {
        improve = true;
        bestFoundCost = unsatClauses->GetSize();
        bestCostTime = TimeElapsed();
    }
    return improve;
}

int LsSolver::PickCriticalMoveBool()
{
    int bestVarIdx = -1;
    int bestScore = 1;
    int operationIdx = 0;
    for (int i = 0; i < containBoolUnsatClauses->GetSize(); i++) {
        int clauseIdx = containBoolUnsatClauses->GetElementByIndex(i);
        Clause* cl = &(clauses[clauseIdx]);
        for (int lSignIdx : cl->boolLiterals) {
            AddBoolOperation(true, lSignIdx, operationIdx);
        }
    }
    for (int i = 0; i < operationIdx; i++) {
        isChosenBoolVar[operationVarIdxBoolVec[i]] = false;
    } // recover chosenBoolVar
    SelectBestOperationFromBoolVec(operationIdx, bestScore, bestVarIdx);
    // if there is untabu decreasing move
    if (bestVarIdx != -1) {
        return bestVarIdx;
    }
    // update weight
    if (mt() % K_WEIGHT_PROB_BASE > smoothProbability) {
        UpdateClauseWeight();
    } else {
        SmoothClauseWeight();
    }
    RandomWalk();
    return -1;
}

void LsSolver::AddBoolOperation(bool useTabu, int litIdx, int& operationIdxBool)
{
    int64_t boolVarIdx = lits[std::abs(litIdx)].delta.ToInt();
    if (isChosenBoolVar[boolVarIdx]) {
        return; // operations will not be inserted repeatedly
    }
    if (!useTabu || (useTabu && outerLayerStep > tabulist[K_DIR_COUNT * boolVarIdx])) { // tabu mechanism
        operationVarIdxBoolVec[operationIdxBool++] = static_cast<int>(boolVarIdx);
        isChosenBoolVar[boolVarIdx] = true;
    }
}

// calculate the operation to be added
void LsSolver::AddCoff(uint64_t varIdxCurr, bool useTabu, int litIdx, int& operationIdx, RationNum coff1)
{
    if (coff1 == 0) {
        return;
    }
    Lit* l = &(lits[std::abs(litIdx)]);
    RationNum litDelta = l->delta;
    if (l->isEqual) {
        if (litIdx > 0) {
            InsertOperation(varIdxCurr, (-litDelta / coff1), operationIdx, useTabu);
        } else {
            InsertOperation(varIdxCurr, RationNum(1), operationIdx, useTabu);
            InsertOperation(varIdxCurr, RationNum(-1), operationIdx, useTabu);
        } // the delta should be !=0, while it is now 0, so the change value should be +/- 1
    } else {
        if (litIdx > 0) {
            InsertOperation(varIdxCurr, ((-litDelta) / coff1), operationIdx, useTabu);
        } else {
            InsertOperation(varIdxCurr, ((1 - litDelta) / coff1), operationIdx, useTabu);
        } // the delta should be >0, while it is now <=0, so the change value should add (1-delta)/coff
    }
}

// for a falsified NIA lit, choose critical move from it
void LsSolver::AddOperationFromFalseLit(bool useTabu, int litIdx, int& operationIdx)
{
    if (falseLitOccur->IsInArray(std::abs(litIdx))) {
        return;
    }
    // if the false lit has been considered, then the lit will not be considered repeatedly
    falseLitOccur->InsertElement(std::abs(litIdx));
    // go through the coffVars and insert critical move for each var
    for (const auto& cv : lits[std::abs(litIdx)].coffVars) {
        AddCoff(cv.varIdx, useTabu, litIdx, operationIdx, cv.coff);
    }
}
// select best bool operation from
void LsSolver::SelectBestOperationFromBoolVec(int operationIdxBool, int& bestScoreBool, int& bestVarIdxBool)
{
    int cnt;
    int score;
    int varIdx;
    uint64_t bestLastMove(UINT64_MAX);
    bool bms;
    if (operationIdxBool > K_BMS_THRESHOLD) {
        bms = true;
        cnt = K_BMS_THRESHOLD;
    } else {
        bms = false;
        cnt = operationIdxBool;
    }
    for (int i = 0; i < cnt; i++) {
        if (bms) {
            int idx = mt() % (operationIdxBool - i);
            int tmp = operationVarIdxBoolVec[operationIdxBool - i - 1];
            varIdx = operationVarIdxBoolVec[idx];
            operationVarIdxBoolVec[idx] = tmp;
        } else {
            varIdx = operationVarIdxBoolVec[i];
        }
        score = vars[varIdx].score;
        uint64_t lastMoveStep = lastMove[K_DIR_COUNT * varIdx];
        if (score > bestScoreBool || (score == bestScoreBool && lastMoveStep < bestLastMove)) {
            bestScoreBool = score;
            bestVarIdxBool = varIdx;
            bestLastMove = lastMoveStep;
        }
    }
}
// select the best nia operation from operationVec depending on score
void LsSolver::SelectBestOperationFromVec(int operationIdx, int& bestScore, int& bestVarIdx, RationNum& bestValue)
{
    bool bms;
    int cnt;
    int score;
    uint64_t operationVarIdx;
    uint64_t bestLastMove(UINT64_MAX);
    RationNum operationChangeValue;
    RationNum bestFutureAbsValue(INT64_MAX);
    RationNum futureAbsValue;
    if (operationIdx > K_BMS_THRESHOLD) {
        bms = true;
        cnt = K_BMS_THRESHOLD;
    } else {
        bms = false;
        cnt = operationIdx;
    }
    for (int i = 0; i < cnt; i++) {
        if (bms) {
            int idx = mt() % (operationIdx - i);
            operationChangeValue = operationChangeValueVec[idx];
            operationVarIdx = operationVarIdxVec[idx];
            operationChangeValueVec[idx] = operationChangeValueVec[operationIdx - i - 1];
            operationVarIdxVec[idx] = operationVarIdxVec[operationIdx - i - 1];
        } else {
            operationChangeValue = operationChangeValueVec[i];
            operationVarIdx = operationVarIdxVec[i];
        }
        futureAbsValue = (solution[operationVarIdx] + operationChangeValue).Abs();
        score = CriticalScore(operationVarIdx, operationChangeValue);
        int oppositeDirection =
            (operationChangeValue > 0) ? 1 : 0; // if the change value is >0, then means it is moving forward, the
                                                // opposite direction is 1(backward)
        uint64_t lastMoveStep = lastMove[2 * operationVarIdx + oppositeDirection];
        if (score > bestScore || (score == bestScore && futureAbsValue < bestFutureAbsValue) ||
            (score == bestScore && futureAbsValue == bestFutureAbsValue && lastMoveStep < bestLastMove)) {
            bestScore = score;
            bestVarIdx = static_cast<int>(operationVarIdx);
            bestValue = operationChangeValue;
            bestLastMove = lastMoveStep;
            bestFutureAbsValue = futureAbsValue;
        }
    }
}
// pick a NIA critical move
int LsSolver::PickCriticalMove(RationNum& bestValue)
{
    int bestScore(1);
    int bestVarIdx(-1);
    int operationIdx(0);
    // determine the critical value from unsat sat, using tabu
    for (int i = 0; i < unsatClauses->GetSize(); i++) {
        Clause* cl = &(clauses[unsatClauses->GetElementByIndex(i)]);
        for (int lIdx : cl->niaLiterals) {
            AddOperationFromFalseLit(true, lIdx, operationIdx);
        }
    }
    // recover the falseLit
    falseLitOccur->Clear();
    // go through the forward and backward move of vars, evaluate their score, pick the untabued best one
    SelectBestOperationFromVec(operationIdx, bestScore, bestVarIdx, bestValue);
    // if there is untabu decreasing move
    if (bestVarIdx != -1) {
        return bestVarIdx;
    }
    // choose from swap operations if there is no decreasing unsat critical
    if (!satClauseWithFalseLiteral->IsEmpty()) {
        operationIdx = 0;
        AddSwapOperation(operationIdx);
        // recover the falseLit
        falseLitOccur->Clear();
        SelectBestOperationFromVec(operationIdx, bestScore, bestVarIdx, bestValue);
        if (bestVarIdx != -1) {
            return bestVarIdx;
        }
    }
    // update weight and random walk
    if (mt() % K_WEIGHT_PROB_BASE > smoothProbability) {
        UpdateClauseWeight();
    } else {
        SmoothClauseWeight();
    }
    RandomWalk();
    return -1;
}

// make move
void LsSolver::CriticalMove(uint64_t varIdx, RationNum changeValue)
{
    int direction = (changeValue > 0) ? 0 : 1;
    if (vars[varIdx].isNia) {
        lastOpValue = changeValue;
        lastOpVar = varIdx;
        MoveUpdate(varIdx, changeValue);
        solution[varIdx] += changeValue;
    } else {
        lastOpVar = UINT64_MAX; // if last operation is boolean operation, the var should no longer be banned
        int originScore = vars[varIdx].score;
        MoveUpdate(varIdx);
        solution[varIdx] *= -1;
        vars[varIdx].score = -originScore;
    }
    // step
    if (vars[varIdx].isNia) {
        lastMove[K_DIR_COUNT * varIdx + direction] = step;
        tabulist[varIdx * K_DIR_COUNT + (direction + 1) % K_DIR_COUNT] =
            step + K_TABU_BASE_NIA + mt() % K_TABU_RAND_NIA;
    } else {
        lastMove[K_DIR_COUNT * varIdx] = outerLayerStep;
        tabulist[K_DIR_COUNT * varIdx] = outerLayerStep + K_TABU_BASE_BOOL + mt() % K_TABU_RAND_BOOL;
        outerLayerStep++;
    }
}
// transfer the ">" to "<="
void LsSolver::InvertLit(Lit& l)
{
    l.key = 1 - l.key;
    for (int i = 0; i < l.coffVars.size(); i++) {
        l.coffVars[i].coff *= -1;
    }
}
// all coffs are positive, go through all vars of the literal
RationNum LsSolver::DeltaLit(Lit& l)
{
    RationNum delta = l.key;
    for (const auto& cv : l.coffVars) {
        delta += (cv.coff * solution[cv.varIdx]);
    }
    return delta;
}

double LsSolver::TimeElapsed()
{
    std::chrono::steady_clock::time_point finish = std::chrono::steady_clock::now();
    std::chrono::duration<double> duration = finish - start;
    return duration.count();
}

void LsSolver::InsertOperation(uint64_t varIdx, RationNum changeValue, int& operationIdx, bool useTabu)
{
    if (varIdx == unchangedVar1 || varIdx == unchangedVar2) {
        return;
    }
    if (varIdx == lastOpVar && changeValue == -lastOpValue) {
        return;
    } // if op returns to previous assignment, it is banned
    uint64_t direction = (changeValue > 0) ? 0 : 1;
    if (useTabu && step < tabulist[K_DIR_COUNT * varIdx + direction]) {
        return;
    } // the operation is now tabued
    RationNum futureSolution = solution[varIdx] + changeValue;
    if (futureSolution > K_SOLUTION_LIMIT || futureSolution < -K_SOLUTION_LIMIT) {
        return;
    }
    bool noPreValue = (preValue1[varIdx] == INT32_MAX && preValue2[varIdx] == INT32_MAX &&
                       futureSolution >= vars[varIdx].lowBound && futureSolution <= vars[varIdx].upperBound);
    bool hasPreValue1 =
        (preValue1[varIdx] != INT32_MAX && preValue2[varIdx] == INT32_MAX && futureSolution == preValue1[varIdx]);
    bool hasPreValue2 = (preValue1[varIdx] != INT32_MAX && preValue2[varIdx] != INT32_MAX &&
                         (futureSolution == preValue1[varIdx] || futureSolution == preValue2[varIdx]));
    if (noPreValue || hasPreValue1 || hasPreValue2) {
        operationVarIdxVec[operationIdx] = varIdx;
        operationChangeValueVec[operationIdx++] = changeValue;
    }
}

void LsSolver::ProcessClauseNiaLiterals(Clause* cl, int& operationIdx)
{
    for (int lIdx : cl->niaLiterals) {
        if ((lits[std::abs(lIdx)].isTrue ^ lIdx) < 0) {
            AddOperationFromFalseLit(true, lIdx, operationIdx);
        } // determine a false lit, and add operation from it
    }
}

void LsSolver::AddSwapOperation(int& operationIdx)
{
    int clauseIdx;
    Clause* cl;
    if (satClauseWithFalseLiteral->GetSize() < K_SWAP_SMALL_THRESHOLD) {
        for (int i = 0; i < satClauseWithFalseLiteral->GetSize(); i++) {
            clauseIdx = satClauseWithFalseLiteral->GetElementByIndex(i);
            cl = &(clauses[clauseIdx]);
            ProcessClauseNiaLiterals(cl, operationIdx);
        }
    } else {
        for (int i = 0; operationIdx < K_SWAP_SMALL_THRESHOLD && i < K_SWAP_MAX_ITER; i++) {
            clauseIdx = satClauseWithFalseLiteral->GetElementByIndex(mt() % satClauseWithFalseLiteral->GetSize());
            cl = &(clauses[clauseIdx]);
            ProcessClauseNiaLiterals(cl, operationIdx);
        }
    }
}

void LsSolver::SetLitMakeBreak(const std::vector<VarLit>& varLits, int vlIdx, uint64_t& currLitIdx,
    RationNum& currLitDeltaNew, const RationNum& changeValue)
{
    auto& vl = varLits[vlIdx];
    if (currLitIdx != vl.litIdx) {
        currLitIdx = vl.litIdx;
        currLitDeltaNew = lits[currLitIdx].delta;
    } // enter a new lit
    currLitDeltaNew += vl.coff * changeValue;
    bool isLastVlOfLit = (vlIdx == varLits.size() - 1) || (currLitIdx != varLits[vlIdx + 1].litIdx);
    if (!isLastVlOfLit) {
        return;
    }
    // the last vlt of the var or the last vlt of current lit
    if (lits[currLitIdx].isEqual) {
        if (lits[currLitIdx].delta == 0 && currLitDeltaNew != 0) {
            litMakeBreak[currLitIdx] = -1;
        } else if (lits[currLitIdx].delta != 0 && currLitDeltaNew == 0) {
            litMakeBreak[currLitIdx] = 1;
        }
    } else {
        if (lits[currLitIdx].delta <= 0 && currLitDeltaNew > 0) {
            litMakeBreak[currLitIdx] = -1;
        } else if (lits[currLitIdx].delta > 0 && currLitDeltaNew <= 0) {
            litMakeBreak[currLitIdx] = 1;
        }
    } // nia <= lit
}

// calculate score for nia vars
int LsSolver::CriticalScore(uint64_t varIdx, RationNum changeValue)
{
    int criticalScore = 0;
    Variable* var = &(vars[varIdx]);
    uint64_t currLitIdx = var->varLits[0].litIdx;
    RationNum currLitDeltaNew = lits[currLitIdx].delta;
    // determine the litMakeBreak by going through the vlt of var
    for (int vlIdx = 0; vlIdx < var->varLits.size(); vlIdx++) {
        SetLitMakeBreak(var->varLits, vlIdx, currLitIdx, currLitDeltaNew, changeValue);
    }
    // determine the score by going through the clauses of var
    Clause* c;
    for (int clsIdx : var->clauseIdxs) {
        c = &(clauses[clsIdx]);
        int clauseSatCountNew = c->satCount;
        for (int vLit : c->literals) {
            clauseSatCountNew += (vLit > 0) ? litMakeBreak[vLit] : (-litMakeBreak[-vLit]);
        }
        if (c->satCount > 0 && clauseSatCountNew == 0) {
            criticalScore -= c->weight;
        } else if (c->satCount == 0 && clauseSatCountNew > 0) {
            criticalScore += c->weight;
        }
    }
    // recover the litMakeBreak
    for (uint64_t lIdx : var->literalIdxs) {
        litMakeBreak[lIdx] = 0;
    }
    return criticalScore;
}

// 更新单个 literal 的 delta 值
void LsSolver::UpdateSingleLitDelta(uint64_t litIdx, RationNum currLitDeltaNew)
{
    if (lits[litIdx].isEqual) {
        if (lits[litIdx].delta == 0 && currLitDeltaNew != 0) {
            lits[litIdx].isTrue = -1;
        }
        if (lits[litIdx].delta != 0 && currLitDeltaNew == 0) {
            lits[litIdx].isTrue = 1;
        }
    } else {
        if (lits[litIdx].delta <= 0 && currLitDeltaNew > 0) {
            lits[litIdx].isTrue = -1;
        }
        if (lits[litIdx].delta > 0 && currLitDeltaNew <= 0) {
            lits[litIdx].isTrue = 1;
        }
    }
    lits[litIdx].delta = currLitDeltaNew;
}

void LsSolver::UpdateBooleanVarScoreInClause(
    int clauseIdx, int clauseSatCountOld, int clauseSatCountNew, int watchLitIdxOld)
{
    Clause* c = &(clauses[clauseIdx]);
    Lit* l;
    if (clauseSatCountOld == 0 && clauseSatCountNew > 0) {
        for (int lSignIdx : c->boolLiterals) {
            l = &(lits[std::abs(lSignIdx)]);
            vars[l->delta.ToInt()].score -= c->weight;
        }
    } else if (clauseSatCountOld == 1 && clauseSatCountNew > 1) {
        l = &(lits[std::abs(watchLitIdxOld)]);
        if (!l->isNiaLit) {
            vars[l->delta.ToInt()].score += c->weight;
        }
    } else if (clauseSatCountOld > 0 && clauseSatCountNew == 0) {
        for (int lSignIdx : c->boolLiterals) {
            l = &(lits[std::abs(lSignIdx)]);
            vars[l->delta.ToInt()].score += c->weight;
        }
    } else if (clauseSatCountOld > 1 && clauseSatCountNew == 1) {
        l = &(lits[std::abs(c->watchLitIdx)]);
        if (!l->isNiaLit) {
            vars[l->delta.ToInt()].score -= c->weight;
        }
    }
}

void LsSolver::UpdateClauseSatCountInVar(uint64_t varIdx)
{
    for (int clsIdx : vars[varIdx].clauseIdxs) {
        Clause* c = &(clauses[clsIdx]);
        int clauseSatCountOld = c->satCount;
        int watchLitIdxOld = c->watchLitIdx;
        c->satCount = 0;
        for (int lIdx : c->literals) {
            if ((lIdx ^ lits[std::abs(lIdx)].isTrue) >= 0) {
                c->satCount++;
                c->watchLitIdx = lIdx;
            }
        }
        if (c->satCount > 0 && clauseSatCountOld == 0) {
            SatAClause(clsIdx);
            litInUnsatClauseNum -= c->literals.size();
            boolLitInUnsatClauseNum -= c->boolLiterals.size();
        } else if (c->satCount == 0 && clauseSatCountOld > 0) {
            UnsatAClause(clsIdx);
            litInUnsatClauseNum += c->literals.size();
            boolLitInUnsatClauseNum += c->boolLiterals.size();
        }
        if (c->satCount > 0 && c->satCount < static_cast<int>(c->literals.size())) {
            satClauseWithFalseLiteral->InsertElement(clsIdx);
        } else {
            satClauseWithFalseLiteral->DeleteElement(clsIdx);
        }
        UpdateBooleanVarScoreInClause(clsIdx, clauseSatCountOld, c->satCount, watchLitIdxOld);
    }
}

void LsSolver::MoveUpdate(uint64_t varIdx, RationNum changeValue)
{
    Variable* var = &(vars[varIdx]);
    VarLit* vl;
    uint64_t currLitIdx = var->varLits[0].litIdx;
    RationNum currLitDeltaNew = lits[currLitIdx].delta;
    int varLitsSize = var->varLits.size();
    for (int vlIdx = 0; vlIdx < varLitsSize; vlIdx++) {
        vl = &(var->varLits[vlIdx]);
        if (currLitIdx != vl->litIdx) {
            currLitIdx = vl->litIdx;
            currLitDeltaNew = lits[currLitIdx].delta;
        }
        currLitDeltaNew += vl->coff * changeValue;
        bool isLastVlOfLit = (vlIdx == varLitsSize - 1) || (currLitIdx != var->varLits[vlIdx + 1].litIdx);
        if (!isLastVlOfLit) {
            continue;
        }
        UpdateSingleLitDelta(currLitIdx, currLitDeltaNew);
    }
    UpdateClauseSatCountInVar(varIdx);
}

// dedicated for boolean var
void LsSolver::UpdateClauseSatCountBool(int clauseIdx, int makeBreakInClause)
{
    Clause* cp = &(clauses[clauseIdx]);
    if (cp->satCount > 0 && cp->satCount + makeBreakInClause == 0) {
        UnsatAClause(clauseIdx);
        litInUnsatClauseNum += cp->literals.size();
        boolLitInUnsatClauseNum += cp->boolLiterals.size();
    } else if (cp->satCount == 0 && cp->satCount + makeBreakInClause > 0) {
        SatAClause(clauseIdx);
        litInUnsatClauseNum -= cp->literals.size();
        boolLitInUnsatClauseNum -= cp->boolLiterals.size();
    }
    cp->satCount += makeBreakInClause;
    if (cp->satCount > 0 && cp->satCount < static_cast<int>(cp->literals.size())) {
        satClauseWithFalseLiteral->InsertElement(clauseIdx);
    } else {
        satClauseWithFalseLiteral->DeleteElement(clauseIdx);
    }
}

void LsSolver::UpdateWatchLitBool(int clauseIdx, int vLitIdx, int clSignIdx, int originSatCount)
{
    Clause* cp = &(clauses[clauseIdx]);
    int originWatchLit = cp->watchLitIdx;
    if (std::abs(originWatchLit) == vLitIdx && cp->satCount > 0) {
        for (int lIdx : cp->literals) {
            if ((lIdx ^ lits[std::abs(lIdx)].isTrue) >= 0) {
                cp->watchLitIdx = lIdx;
                break;
            }
        }
    } else if (originSatCount == 0) {
        cp->watchLitIdx = (clSignIdx > 0) ? (vLitIdx) : (-vLitIdx);
    }
}

void LsSolver::UpdateBooleanVarScoreInClauseBool(int clauseIdx, int makeBreakInClause, int originSatCount)
{
    Clause* cp = &(clauses[clauseIdx]);
    Lit* l;
    if (makeBreakInClause > 0) {
        if (originSatCount == 0) {
            for (int bl : cp->boolLiterals) {
                l = &(lits[std::abs(bl)]);
                vars[l->delta.ToInt()].score -= cp->weight;
            }
        } else if (originSatCount == 1) {
            l = &(lits[std::abs(cp->watchLitIdx)]);
            if (!l->isNiaLit) {
                vars[l->delta.ToInt()].score += cp->weight;
            }
        }
    } else if (makeBreakInClause < 0) {
        if (cp->satCount == 0) {
            for (int bl : cp->boolLiterals) {
                l = &(lits[std::abs(bl)]);
                vars[l->delta.ToInt()].score += cp->weight;
            }
        } else if (cp->satCount == 1) {
            l = &(lits[std::abs(cp->watchLitIdx)]);
            if (!l->isNiaLit) {
                vars[l->delta.ToInt()].score -= cp->weight;
            }
        }
    }
}

void LsSolver::MoveUpdate(uint64_t varIdx)
{
    Variable* var = &(vars[varIdx]);
    int vLitIdx = static_cast<int>(var->literalIdxs[0]);
    lits[vLitIdx].isTrue *= -1;
    int varClauseIdxsSize = var->clauseIdxs.size();
    for (int i = 0; i < varClauseIdxsSize; i++) {
        int clSignIdx = var->clauseIdxs[i];
        int makeBreakInClause = 1;
        if ((solution[varIdx] > 0 && var->boolVarInPosClause[i]) ||
            (solution[varIdx] < 0 && !var->boolVarInPosClause[i])) {
            makeBreakInClause = -1;
        }
        int clauseIdx = std::abs(clSignIdx);
        int originSatCount = clauses[clauseIdx].satCount;
        UpdateClauseSatCountBool(clauseIdx, makeBreakInClause);
        UpdateWatchLitBool(clauseIdx, vLitIdx, clSignIdx, originSatCount);
        UpdateBooleanVarScoreInClauseBool(clauseIdx, makeBreakInClause, originSatCount);
    }
}

// check
int LsSolver::CheckSingleClause(Clause* cp)
{
    int satCount = 0;
    for (int litIdx : cp->literals) {
        RationNum delta = lits[std::abs(litIdx)].delta;
        bool isEqual = lits[std::abs(litIdx)].isEqual;
        if (!lits[std::abs(litIdx)].isNiaLit) {
            int64_t varIdx = lits[std::abs(litIdx)].delta.ToInt();
            if ((solution[varIdx] > 0 && litIdx > 0) || (solution[varIdx] < 0 && litIdx < 0)) {
                satCount++;
            }
        } else if ((!isEqual && ((delta <= 0 && litIdx > 0) || (delta > 0 && litIdx < 0))) ||
                   (isEqual && ((delta == 0 && litIdx > 0) || (delta != 0 && litIdx < 0)))) {
            satCount++;
        }
    }
    return satCount;
}

bool LsSolver::CheckSolution()
{
    Clause* cp;
    int unsatNum = 0;
    for (int litIdx = 0; litIdx < lits.size(); litIdx++) {
        if (!litAppear[litIdx] || !lits[litIdx].isNiaLit) {
            continue;
        }
        RationNum delta = DeltaLit(lits[litIdx]);
        if (delta != lits[litIdx].delta) {
            std::cout << "Lit delta wrong: " << litIdx << "\n";
        }
    } // check Lit delta
    for (uint64_t i = 0; i < numClauses; i++) {
        cp = &(clauses[i]);
        int satCount = CheckSingleClause(cp);
        if (satCount != cp->satCount) {
            std::cout << "sat count wrong at Clause " << i << "\n";
        }
        if (satCount == 0) {
            unsatNum++;
        }
    }
    for (int varIdx = 0; varIdx < vars.size(); varIdx++) {
        if (solution[varIdx] > vars[varIdx].upperBound || solution[varIdx] < vars[varIdx].lowBound) {
            std::cout << "var " << varIdx << " out of range\n";
        }
    }
    if (unsatNum == unsatClauses->GetSize()) {
        std::cout << "right solution\n";
    } else {
        std::cout << "wrong solution\n";
    }
    return unsatNum == unsatClauses->GetSize();
}

bool LsSolver::UpdateInnerBestSolution()
{
    if (unsatClauses->GetSize() < bestFoundHardCostThisNia) {
        bestFoundHardCostThisNia = unsatClauses->GetSize();
        return true;
    }
    return false;
}

bool LsSolver::UpdateOuterBestSolution()
{
    if (unsatClauses->GetSize() < bestFoundHardCostThisBool) {
        bestFoundHardCostThisBool = unsatClauses->GetSize();
        return true;
    }
    return false;
}

void LsSolver::EnterNiaMode()
{
    bestFoundHardCostThisNia = unsatClauses->GetSize();
    if (isInBoolSearch) {
        noImproveCntNia = 0;
    } // only when it is now in boolean mode, the noImproveCntNia will be 0
    isInBoolSearch = false;
}

void LsSolver::EnterBoolMode()
{
    bestFoundHardCostThisBool = unsatClauses->GetSize();
    if (!isInBoolSearch) {
        noImproveCntBool = 0;
    } // only when it is now in integer mode, the noImproveCntBool will be 0
    isInBoolSearch = true;
}

// local search
bool LsSolver::LocalSearch(const std::map<std::string, double>& varInitial)
{
    Initialize(varInitial);
    if (buildUnsat) {
        return false;
    }
    int noImproveCnt = 0;
    int flipv;
    RationNum changeValue = RationNum(0);
    start = std::chrono::steady_clock::now();
    outerLayerStep = 1;
    for (step = 1; step < maxStep; step++) {
        if (unsatClauses->GetSize() == 0) {
            UpBoolVars();
            return true;
        }
        bool timeUpBool = (noImproveCntBool * litInUnsatClauseNum > 5 * boolLitInUnsatClauseNum);
        bool timeUpNia = (noImproveCntNia * litInUnsatClauseNum > 20 * (litInUnsatClauseNum - boolLitInUnsatClauseNum));
        if ((isInBoolSearch && boolLitInUnsatClauseNum < litInUnsatClauseNum && timeUpBool) ||
            boolLitInUnsatClauseNum == 0) {
            EnterNiaMode();
        } else if ((!isInBoolSearch && boolLitInUnsatClauseNum > 0 && timeUpNia) ||
                   (litInUnsatClauseNum == boolLitInUnsatClauseNum)) {
            EnterBoolMode();
        }
        if (isInBoolSearch) {
            flipv = PickCriticalMoveBool();
            if (flipv != -1) {
                CriticalMove(flipv, changeValue);
            }
            noImproveCntBool = UpdateOuterBestSolution() ? 0 : (noImproveCntBool + 1);
        } else {
            flipv = PickCriticalMove(changeValue);
            if (flipv != -1) {
                CriticalMove(flipv, changeValue);
            }
            noImproveCntNia = UpdateInnerBestSolution() ? 0 : (noImproveCntNia + 1);
        }
        noImproveCnt = (UpdateBestSolution()) ? 0 : (noImproveCnt + 1);
    }
    return false;
}

void LsSolver::UpdateNiaVar(size_t vIdx)
{
    if (!varAppear[vIdx]) {
        if (vars[vIdx].isNia) {
            int rootIdx = fa[vIdx];
            if (rootIdx != vIdx) {
                solution[vIdx] = solution[rootIdx] * faCoff[vIdx] + faConst[vIdx];
            }
        } else if (upValueVars[vIdx] == 0) {
            solution[vIdx] = -1;
        }
    }
}

bool LsSolver::EvaluateNiaLiteral(Lit* l, int lIdx, RationNum delta)
{
    if (!l->isEqual) {
        if ((delta <= 0 && lIdx > 0) || (delta > 0 && lIdx < 0)) {
            return true;
        }
    } else if ((delta == 0 && lIdx > 0) || (delta != 0 && lIdx < 0)) {
        return true;
    }
    return false;
}

bool LsSolver::CheckNiaLiteralSatisfaction(Lit* l, int lIdx, std::vector<bool>& litAppearTmp)
{
    if (!litAppearTmp[std::abs(lIdx)]) {
        RationNum delta = DeltaLit(lits[std::abs(lIdx)]);
        l->delta = delta;
        litAppearTmp[std::abs(lIdx)] = true;
        return EvaluateNiaLiteral(l, lIdx, delta);
    }
    return EvaluateNiaLiteral(l, lIdx, l->delta);
}

bool LsSolver::CheckLiteralSatisfaction(int lIdx, std::vector<bool>& litAppearTmp)
{
    Lit* l = &(lits[std::abs(lIdx)]);
    if (lIdx > 0 && l->litsIndex == 0) {
        return true;
    } else if (l->isNiaLit) {
        return CheckNiaLiteralSatisfaction(l, lIdx, litAppearTmp);
    } else if ((solution[l->delta.ToInt()] > 0 && lIdx > 0) ||
               (solution[l->delta.ToInt()] < 0 && lIdx < 0)) {
        return true;
    }
    return false;
}

void LsSolver::UpBoolVars()
{
    for (size_t vIdx = 0; vIdx < numVars; vIdx++) {
        UpdateNiaVar(vIdx);
    }

    std::vector<bool> litAppearTmp = litAppear;
    for (int idx = static_cast<int>(reconstructStack.size()) - 1; idx >= 0; idx--) {
        Clause cl = reconstructStack[idx];
        bool satFlag = false;
        for (int lIdx : cl.literals) {
            satFlag = CheckLiteralSatisfaction(lIdx, litAppearTmp);
            if (satFlag) {
                break;
            }
        }
        if (!satFlag) {
            Lit* l = &(lits[std::abs(cl.literals[0])]);
            solution[l->delta.ToInt()] = 1;
        }
    }
}

} // namespace niaOverall
