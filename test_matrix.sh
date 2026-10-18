#!/bin/bash
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_matrix.sh                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ericpayen </var/spool/mail/ericpayen>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/10/18 03:20:37 by ericpayen         #+#    #+#              #
#    Updated: 2026/10/18 20:02:00 by ericpayen        ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
NC='\033[0;0m'
EXEC="./rush-02"

run_matrix_test() {
    local dict_file="$1"
    local input_val="$2"
    local expected_out="$3"
    local test_label="$4"
    
    echo -e "Testing [${BLUE}$test_label${NC}] with \"$input_val\""
    
    # 1. On lance l'exécutable sous Valgrind avec un code d'erreur dédié (42) en cas de fuite
    local raw_output
    raw_output=$(valgrind --leak-check=full --error-exitcode=42 $EXEC "$dict_file" "$input_val" 2>&1)
    local exit_status=$?
    
    # 2. On extrait uniquement la ligne textuelle générée par rush-02 (on ignore les lignes Valgrind qui commencent par ==)
    local out
    out=$(echo "$raw_output" | grep -v '==' | xargs)
    
    # 3. Étape de vérification de la mémoire (Valgrind Exit Monitor)
    if [ $exit_status -eq 42 ]; then
        echo -e "  Result: ${RED}FAIL${NC} 💥 Fuite mémoire ou crash détecté par Valgrind !"
        echo "$raw_output" | grep '==' | tail -n 5
        return 1
    fi

    # 4. Étape de vérification du résultat algorithmique attendu
    if [ "$expected_out" == "Error" ] || [ "$expected_out" == "Dict Error" ]; then
        if echo "$raw_output" | grep -v '==' | grep -q "$expected_out"; then
            echo -e "  Result: ${GREEN}PASS${NC} (stderr match: $expected_out) [Memory: Clean]"
        else
            echo -e "  Result: ${RED}FAIL${NC}\n  Expected error: \"$expected_out\"\n  Got: \"$out\""
        fi
    else
        if [ "$out" == "$expected_out" ]; then
            echo -e "  Result: ${GREEN}PASS${NC} -> \"$out\" [Memory: Clean]"
        else
            echo -e "  Result: ${RED}FAIL${NC}\n  Expected: \"$expected_out\"\n  Got:      \"$out\""
        fi
    fi
}

echo -e "${BLUE}=== STARTING RUSH-02 FULL MATRIX TESTS ===${NC}\n"

# ==============================================================================
# SECTION 1: ALL SINGLE & COMPOUND EXCEPTIONS (ENGLISH)
# ==============================================================================
echo -e "${BLUE}--- Section 1: English Base & Scales ---${NC}"
run_matrix_test "numbers.dict" "0" "zero" "Zero Base"
run_matrix_test "numbers.dict" "11" "eleven" "Teens Exception"
run_matrix_test "numbers.dict" "16" "sixteen" "Teens Exception"
run_matrix_test "numbers.dict" "42" "forty-two" "Compound Tens"
run_matrix_test "numbers.dict" "100" "one hundred" "Hundred Scaler"
run_matrix_test "numbers.dict" "105" "one hundred five" "Hundred Compound"
run_matrix_test "numbers.dict" "1000" "one thousand" "Thousand Scaler"
run_matrix_test "numbers.dict" "1000000" "one million" "Million Scaler"
run_matrix_test "numbers.dict" "1000000000" "one billion" "Billion Scaler"
run_matrix_test "numbers.dict" "1000000000000" "one trillion" "Trillion Scaler"

# ==============================================================================
# SECTION 2: FRENCH SPECIFIC GRAMMAR EXCEPTIONS (70s, 80s, 90s)
# ==============================================================================
echo -e "\n${BLUE}--- Section 2: French Grammar Regionalities ---${NC}"
run_matrix_test "numbers_fr.dict" "21" "vingt et un" "French Conjunction"
run_matrix_test "numbers_fr.dict" "71" "soixante-et-onze" "French 71"
run_matrix_test "numbers_fr.dict" "73" "soixante-treize" "French 73 (60 + 13)"
run_matrix_test "numbers_fr.dict" "80" "quatre-vingts" "French 80 Base"
run_matrix_test "numbers_fr.dict" "81" "quatre-vingt-un" "French 81"
run_matrix_test "numbers_fr.dict" "91" "quatre-vingt-onze" "French 91"
run_matrix_test "numbers_fr.dict" "99" "quatre-vingt-dix-neuf" "French 99 (80 + 19)"

# ==============================================================================
# SECTION 3: BELGIAN & SWISS DICTIONARIES EXCEPTIONS
# ==============================================================================
echo -e "\n${BLUE}--- Section 3: Belgian & Swiss Adaptations ---${NC}"
run_matrix_test "numbers_be.dict" "71" "septante-un" "Belgian 71"
run_matrix_test "numbers_be.dict" "73" "septante-trois" "Belgian 73"
run_matrix_test "numbers_be.dict" "91" "nonante-un" "Belgian 91"
run_matrix_test "numbers_sw.dict" "83" "huitante-trois" "Swiss 83"

# ==============================================================================
# SECTION 4: EXTREME MAX BOUNDARIES & HUGE VALUES
# ==============================================================================
echo -e "\n${BLUE}--- Section 4: Maximum Value Limits & Huge Scaling ---${NC}"
run_matrix_test "numbers.dict" "999999999999999" "nine hundred ninety-nine trillion nine hundred ninety-nine billion nine hundred ninety-nine million nine hundred ninety-nine thousand nine hundred ninety-nine" "Max Trillion Upper Bound"
run_matrix_test "huge.dict" "1000000000000000000000000000000000000000000000000000000000000000" "one vigintillion" "Vigintillion Infinite Scale Check"

echo -e "\n${BLUE}=== MATRIX SEQUENCE COMPLETE ===${NC}"

