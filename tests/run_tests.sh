#!/usr/bin/env bash
# Smoke tests: build each program, feed it scripted input, and check the output.
# Run from the repository root:  bash tests/run_tests.sh
set -u

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
BUILD="$ROOT/build"
WORK="$(mktemp -d)"          # programs write their bill files into the current directory
mkdir -p "$BUILD"
pass=0; fail=0

compile() {
  g++ -std=c++17 -Wall -Wextra -Wpedantic -o "$BUILD/$1" "$ROOT/src/$1.cpp" || { echo "BUILD FAILED: $1"; exit 1; }
}

# check <test name> <program> <input (printf format)> <expected text>...
check() {
  local name="$1" prog="$2" input="$3"; shift 3
  local out; out="$(cd "$WORK" && printf "$input" | timeout 5 "$BUILD/$prog" 2>&1)"
  local ok=1
  for expected in "$@"; do
    if ! grep -qF -- "$expected" <<<"$out"; then ok=0; echo "  missing: $expected"; fi
  done
  if [ $ok -eq 1 ]; then echo "PASS  $name"; pass=$((pass+1)); else echo "FAIL  $name"; echo "$out" | sed 's/^/    | /'; fail=$((fail+1)); fi
}

for p in q1_cafeteria_order_system q2_shopping_cart q3_student_scores q4_bank_account_system; do compile "$p"; done

# ---- Q1 Cafeteria ---------------------------------------------------------------
check "Q1 no discount (R80)"            q1_cafeteria_order_system 'Test\nUser\n4\n1\n2\n3\n4\n' "Total Bill: R80.00" "No discount applied." "Final Bill: R80.00"
check "Q1 exactly R100 gets no discount" q1_cafeteria_order_system 'A\nB\n4\n3\n3\n3\n3\n' "Total Bill: R100.00" "No discount applied."
check "Q1 discount applies (R120 -> R108)" q1_cafeteria_order_system 'A\nB\n3\n8\n8\n8\n' "Total Bill: R120.00" "Discount applied (10%): R12.00" "Final Bill: R108.00"
check "Q1 rejects bad input, then continues" q1_cafeteria_order_system 'A\nB\nabc\n9\n1\n99\nx\n1\n' "Invalid input" "Final Bill: R15.00"
check "Q1 bill file written"            q1_cafeteria_order_system 'Jo\nBloggs\n1\n1\n' "written to CafeteriaBill.txt"
grep -q "Customer: Jo Bloggs" "$WORK/CafeteriaBill.txt" && grep -q "Final Bill: R15.00" "$WORK/CafeteriaBill.txt" \
  && { echo "PASS  Q1 file contents"; pass=$((pass+1)); } || { echo "FAIL  Q1 file contents"; fail=$((fail+1)); }

# ---- Q2 Shopping cart -----------------------------------------------------------
check "Q2 no discount (R200 exactly)"   q2_shopping_cart 'Sam\n8\n5\nn\n' "Total Cost: R200.00" "Discount: R0.00" "Final Total after Discount: R200.00"
check "Q2 5% discount (R240 -> R228)"   q2_shopping_cart 'Sam\n8\n6\nn\n' "Total Cost: R240.00" "Discount: R12.00" "Final Total after Discount: R228.00"
check "Q2 several items, y/n handling"  q2_shopping_cart 'Sam\n1\n2\nmaybe\ny\n2\n1\nN\n' "Please answer with y or n." "2 x Coffee" "1 x Sandwich" "Total Cost: R60.00"
check "Q2 rejects zero/negative quantity" q2_shopping_cart 'Sam\n1\n0\n-3\n1\nn\n' "Invalid input" "Total Cost: R15.00"

# ---- Q3 Scores ------------------------------------------------------------------
check "Q3 sample from the brief"        q3_student_scores '89\n90\n67\n23\n56\n' "Average score: 65.00" "Highest score: 90" "Lowest score: 23" "Student 1: 89" "Student 5: 56"
check "Q3 all equal / lowest is first"  q3_student_scores '10\n50\n60\n70\n80\n' "Lowest score: 10" "Highest score: 80" "Average score: 54.00"
check "Q3 rejects out-of-range input"   q3_student_scores '101\n-1\nabc\n50\n50\n50\n50\n50\n' "Invalid input" "Average score: 50.00"

# ---- Q4 Bank --------------------------------------------------------------------
check "Q4 needs account first"          q4_bank_account_system '2\n6\n' "Please create an account first"
check "Q4 create, deposit, withdraw"    q4_bank_account_system '1\nTest User\n12345\n1000\n2\n500\n3\n200\n4\n6\n' "Account created successfully!" "New balance: R1500.00" "New balance: R1300.00" "Current balance: R1300.00"
check "Q4 rejects overdraw"             q4_bank_account_system '1\nT\n1\n100\n3\n500\n6\n' "Insufficient funds. Current balance: R100.00"
check "Q4 rejects invalid money inputs" q4_bank_account_system '1\nT\n1\n0\n-5\nabc\n100\n2\n-1\n0\n50\n6\n' "Invalid input" "New balance: R150.00"
check "Q4 rejects invalid menu input"   q4_bank_account_system 'x\n9\n6\n' "Invalid input" "Goodbye!"
check "Q4 details screen"               q4_bank_account_system '1\nTest User\n012345\n1000\n5\n6\n' "Account Holder: Test User" "Account Number: 12345" "Current Balance: R1000.00"
check "Q4 replace account asks first"   q4_bank_account_system '1\nA\n1\n100\n1\nn\n5\n6\n' "will be replaced" "Account Holder: A"
check "Q4 exits cleanly when input ends" q4_bank_account_system '1\nA\n' "Input closed"

rm -rf "$WORK"
echo; echo "Passed: $pass   Failed: $fail"
[ $fail -eq 0 ]
