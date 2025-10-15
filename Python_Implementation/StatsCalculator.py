import random

class StatisticsCalculator:
    def __init__(self, numbers):
        """Initialize with a list of numbers"""
        self.numbers = numbers

    def mean(self):
        """Calculate the mean (average)"""
        return sum(self.numbers) / len(self.numbers) if self.numbers else 0

    def median(self):
        """Calculate the median"""
        sorted_nums = sorted(self.numbers)
        n = len(sorted_nums)
        if n == 0:
            return None
        mid = n // 2
        if n % 2 == 0:
            return (sorted_nums[mid - 1] + sorted_nums[mid]) / 2
        else:
            return sorted_nums[mid]

    def mode(self):
        """Calculate the mode(s) using a dictionary"""
        if not self.numbers:
            return []
        freq = {}
        for num in self.numbers:
            freq[num] = freq.get(num, 0) + 1
        max_count = max(freq.values())
        return [num for num, count in freq.items() if count == max_count]

    def display_results(self):
        """Display the statistics"""
        sorted_nums = sorted(self.numbers)
        print("\n--- Statistics Results ---")
        print(f"Original Numbers: {self.numbers}")
        print(f"Sorted Numbers: {sorted_nums}")
        print(f"Mean: {self.mean():.2f}")
        print(f"Median: {self.median()}")
        print(f"Mode: {self.mode()}\n")


def main():
    print("=== Statistics Calculator (Python OOP) ===")
    size = int(input("Enter the size of the list: "))

    print("Choose an option:")
    print("1. Enter numbers manually")
    print("2. Generate random numbers")
    choice = input("Enter choice (1 or 2): ")

    if choice == '1':
        numbers = []
        for i in range(size):
            num = float(input(f"Enter number {i + 1}: "))
            numbers.append(num)
    elif choice == '2':
        lower = int(input("Enter the lower bound for random numbers: "))
        upper = int(input("Enter the upper bound for random numbers: "))
        numbers = [random.randint(lower, upper) for _ in range(size)]
        print(f"Generated list: {numbers}")
    else:
        print("Invalid choice. Exiting.")
        return

    calc = StatisticsCalculator(numbers)
    calc.display_results()


if __name__ == "__main__":
    main()
