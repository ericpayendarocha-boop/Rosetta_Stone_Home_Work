# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_matrix.sh                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ericpayen </var/spool/mail/ericpayen>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/10/18 03:20:37 by ericpayen         #+#    #+#              #
#    Updated: 2026/10/18 03:24:58 by ericpayen        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
NC='\033[0;0m'
EXEC="./rush-02"

rm -f malformed_*.dict order_*.dict custom_*.dict

run_matrix_test() {
    local dict_file="$1"
    local input_val="$2"
    local expected_out="$3"
    local test_label="$4"
    
    echo -e "Testing [${BLUE}$test_label${NC}] with \"$input_val\""
    
    local out
    local err
    out=$( $EXEC "$dict_file" "$input_val" 2>/dev/null | xargs )
    err=$( $EXEC "$dict_file" "$input_val" 2>&1 >/dev/null | xargs )
    
    if [ "$expected_out" == "Error" ] || [ "$expected_out" == "Dict Error" ]; then
        if [ "$err" == "$expected_out" ]; then
            echo -e "  Result: ${GREEN}PASS${NC} (stderr: $expected_out)"
        else
            echo -e "  Result: ${RED}FAIL${NC}\n  Expected stderr: \"$expected_out\"\n  Got stdout:      \"$out\"\n  Got stderr:      \"$err\""
        fi
    else
        if [ "$out" == "$expected_out" ]; then
            echo -e "  Result: ${GREEN}PASS${NC} -> \"$out\""
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
run_matrix_test "numbers_fr.dict" "71" "soixante-et-onze" "French 71 (Direct Exception)"
run_matrix_test "numbers_fr.dict" "73" "soixante-treize" "French 73 (60 + 13)"
run_matrix_test "numbers_fr.dict" "80" "quatre-vingts" "French 80 Base"
run_matrix_test "numbers_fr.dict" "81" "quatre-vingt-un" "French 81 (No Conjunction)"
run_matrix_test "numbers_fr.dict" "91" "quatre-vingt-onze" "French 91 (Direct Exception)"
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
# SECTION 4: EXTREME MAX TRIILLIONS BOUNDARY
# ==============================================================================
echo -e "\n${BLUE}--- Section 4: Maximum Value Limits ---${NC}"
run_matrix_test "numbers.dict" "999999999999999" "nine hundred ninety-nine trillion nine hundred ninety-nine billion nine hundred ninety-nine million nine hundred ninety-nine thousand nine hundred ninety-nine" "Max Trillion Upper Bound"

# ==============================================================================
# SECTION 5: ROBUST DICT PARSING & SPACING RULES
# ==============================================================================
echo -e "\n${BLUE}--- Section 5: Dictionary Space Re-Formatting ---${NC}"
cat << 'EOF' > malformed_spaces.dict
0      :zero

1:      one

10   :    ten
20:twenty
100:hundred
1000:thousand
EOF
run_matrix_test "malformed_spaces.dict" "121" "one hundred twenty-one" "Irregular Spaces & Empty Lines"

# ==============================================================================
# SECTION 6: DESORDER RULES VS COPOSITE OVERRIDES
# ==============================================================================
echo -e "\n${BLUE}--- Section 6: Desorder Rules & Initial Base Constraint ---${NC}"
cat << 'EOF' > custom_composite.dict
1000:thousand
100:hundred
54:fifty-four
50:fifty
20:twenty
10:ten
4:four
1:one
0:zero
EOF
# Must bypass the composite rule "54" and use initial base components 50 + 4
run_matrix_test "custom_composite.dict" "54" "fifty-four" "Enforce Base Initial Decomposition"

# ==============================================================================
# SECTION 7: EXPLICIT DICT ERROR TRIGGERS
# ==============================================================================
echo -e "\n${BLUE}--- Section 7: Strict Dictionary Fault Detection ---${NC}"

# A. Missing Colon Separator
cat << 'EOF' > malformed_syntax1.dict
0:zero
1 one
10:ten
EOF
run_matrix_test "malformed_syntax1.dict" "10" "Dict Error" "Syntax Error (Missing Colon)"

# B. Missing Critical Base Entry for computing sequence
cat << 'EOF' > custom_missing_key.dict
0:zero
1:one
10:ten
100:hundred
EOF
run_matrix_test "custom_missing_key.dict" "21" "Dict Error" "Unresolvable Value Fault"

echo -e "\n${BLUE}=== MATRIX SEQUENCE COMPLETE ===${NC}"
rm -f malformed_*.dict order_*.dict custom_*.dict

