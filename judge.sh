#!/bin/bash

# ============================================================================
# Copyright (c) 2026 Калоян Ивелинов Милчев (Kaloyan Ivelinov Milchev)
# Факултетен номер / Student ID: F118428
# Нов български университет (New Bulgarian University)
# ============================================================================

# ===========================================
# Metro Journey - Judging System
# ===========================================
# Тества решение срещу input/input.txt
# и сравнява с output/output.txt
# ===========================================

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

if [ -z "$1" ]; then
    echo -e "${YELLOW}Използване: ./judge.sh <solution.cpp>${NC}"
    echo ""
    echo "Примери:"
    echo "  ./judge.sh main-NaiveApproach.cpp"
    echo "  ./judge.sh main-GreedySorting.cpp"
    echo "  ./judge.sh main-OptimalApproach.cpp"
    exit 1
fi

SOLUTION=$1
EXECUTABLE="solution_temp"

echo -e "${BLUE}========================================${NC}"
echo -e "${BLUE}   Metro Journey Judging System${NC}"
echo -e "${BLUE}========================================${NC}"
echo ""

# Компилиране
echo -e "${YELLOW}[1/3] Компилиране на $SOLUTION...${NC}"
g++ -O2 -o $EXECUTABLE $SOLUTION 2> compile_error.txt

if [ $? -ne 0 ]; then
    echo -e "${RED}✗ ГРЕШКА ПРИ КОМПИЛАЦИЯ${NC}"
    cat compile_error.txt
    rm -f compile_error.txt
    exit 1
fi

echo -e "${GREEN}✓ Компилацията успешна${NC}"
rm -f compile_error.txt
echo ""

# Проверка за файлове
if [ ! -f "input/input.txt" ] || [ ! -f "output/output.txt" ]; then
    echo -e "${RED}✗ Липсват input/input.txt или output/output.txt${NC}"
    echo "Първо стартирай генератора: ./generator"
    rm -f $EXECUTABLE
    exit 1
fi

# Изпълнение
echo -e "${YELLOW}[2/3] Изпълнение на решението...${NC}"

START_TIME=$(date +%s%N)
./$EXECUTABLE < input/input.txt > user_output.txt 2>/dev/null
EXIT_CODE=$?
END_TIME=$(date +%s%N)

ELAPSED=$(( (END_TIME - START_TIME) / 1000000 ))

if [ $EXIT_CODE -ne 0 ]; then
    echo -e "${RED}✗ RUNTIME ERROR (exit code: $EXIT_CODE)${NC}"
    rm -f $EXECUTABLE user_output.txt
    exit 1
fi

echo -e "${GREEN}✓ Изпълнено за ${ELAPSED}ms${NC}"
echo ""

# Сравнение
echo -e "${YELLOW}[3/3] Сравнение на резултатите...${NC}"
echo ""

TOTAL=$(wc -l < output/output.txt | tr -d ' ')
PASSED=0
FAILED=0

while IFS= read -r expected && IFS= read -r actual <&3; do
    expected=$(echo "$expected" | tr -d '\r\n ')
    actual=$(echo "$actual" | tr -d '\r\n ')
    
    if [ "$expected" = "$actual" ]; then
        PASSED=$((PASSED + 1))
    else
        FAILED=$((FAILED + 1))
        if [ $FAILED -le 5 ]; then
            echo -e "${RED}✗ Test $((PASSED + FAILED)): Expected $expected, got $actual${NC}"
        fi
    fi
done < output/output.txt 3< user_output.txt

# Резултати
echo ""
echo -e "${BLUE}========================================${NC}"
echo -e "${BLUE}   Резултати${NC}"
echo -e "${BLUE}========================================${NC}"
echo -e "  Общо тестове:  $TOTAL"
echo -e "  ${GREEN}Успешни:       $PASSED${NC}"
echo -e "  ${RED}Неуспешни:     $FAILED${NC}"
echo -e "  Време:         ${ELAPSED}ms"

if [ $FAILED -eq 0 ]; then
    echo ""
    echo -e "${GREEN}★★★ ВСИЧКИ ТЕСТОВЕ ПРЕМИНАХА УСПЕШНО! ★★★${NC}"
    SCORE=100
else
    SCORE=$((PASSED * 100 / TOTAL))
fi

echo ""
echo -e "  Резултат: ${YELLOW}$SCORE%${NC} ($PASSED/$TOTAL)"
echo -e "${BLUE}========================================${NC}"

# Почистване
rm -f $EXECUTABLE user_output.txt
