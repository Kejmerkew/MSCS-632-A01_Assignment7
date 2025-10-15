(* ---------- Statistics Calculator in OCaml (Functional) ---------- *)
open Printf

(* ---------- Helper Functions ---------- *)

(* Read a list of floats manually *)
let rec read_list n acc =
  if n <= 0 then List.rev acc
  else (
    printf "Enter number %d: " ((List.length acc) + 1);
    let num = read_float () in
    read_list (n - 1) (num :: acc)
  )

(* Generate random float list between 1 and 100 *)
let rec generate_random_list n =
  if n <= 0 then []
  else (Random.float 100.0) :: generate_random_list (n - 1)

(* Mean: sum / length *)
let mean lst =
  let total = List.fold_left ( +. ) 0.0 lst in
  total /. float_of_int (List.length lst)

(* Median: middle value or average of two middle values *)
let median lst =
  let sorted = List.sort compare lst in
  let len = List.length sorted in
  if len mod 2 = 1 then
    List.nth sorted (len / 2)
  else
    let mid1 = List.nth sorted ((len / 2) - 1) in
    let mid2 = List.nth sorted (len / 2) in
    (mid1 +. mid2) /. 2.0

(* Mode: most frequent element(s) *)
let mode lst =
  let sorted = List.sort compare lst in
  let rec count_freq l current count acc max_count =
    match l with
    | [] ->
        if count > max_count then [current]
        else if count = max_count then current :: acc
        else acc
    | x :: xs ->
        if x = current then count_freq xs current (count + 1) acc max_count
        else if count > max_count then count_freq xs x 1 [current] count
        else if count = max_count then count_freq xs x 1 (current :: acc) max_count
        else count_freq xs x 1 acc max_count
  in
  match sorted with
  | [] -> []
  | x :: xs -> count_freq xs x 1 [] 1

(* ---------- Main Program ---------- *)

let () =
  Random.self_init ();
  printf "Enter the number of elements: ";
  let n = read_int () in
  printf "Choose input method:\n1. Manual entry\n2. Random generation\n> ";
  let choice = read_int () in
  let numbers =
    if choice = 1 then read_list n []
    else generate_random_list n
  in

  printf "\nOriginal Numbers: ";
  List.iter (fun x -> printf "%.2f " x) numbers;
  printf "\n";

  (* Sort once for display and median/mode calculations *)
  let sorted_numbers = List.sort compare numbers in
  printf "\n";
  printf "Sorted Numbers: ";
  List.iter (fun x -> printf "%.2f " x) sorted_numbers;
  printf "\n";

  let m = mean sorted_numbers in
  let med = median sorted_numbers in
  let modes = mode sorted_numbers in

  printf "\nMean: %.2f\n" m;
  printf "Median: %.2f\n" med;
  printf "Mode(s): ";
  List.iter (fun x -> printf "%.2f " x) modes;
  printf "\n"
