# Personal Finance Manager (C++)

Welcome to **Personal Finance Manager**, a simple command-line tool written in C++ to help you track your income, expenses, and overall financial activity. This app makes it easy to register as a user, log in securely, record various transactions, receive financial summaries, and get basic advice on managing your finances.

## Features

- **User Registration and Login**  
  Securely create a new account and log in to your personal space.

- **Add Financial Records**  
  Track income and expenses with date, category, amount, and type.

- **View/Delete Records**  
  Review past transactions or delete unwanted records.

- **Income/Expense Summary**  
  Calculate and view overall financial statistics.

- **Basic Financial Advisor**  
  Get simple tips on saving and spending better.

## Main Program Structure

The main logic resides in [`Project.cpp`](https://github.com/AliRaza-033/Personal_Finance_Manager_Cpp/blob/Project/Project.cpp).
Key modules:
- **registerUser / loginUser** – Handles user creation and authentication.
- **addRecord / viewRecords / deleteRecord** – Transaction management.
- **calculateSummary** – Provides a summary of income and expenses.
- **financialAdvisor** – Prints basic financial tips.

Records are stored in plain text files (`records.txt`, `user.txt`) for simplicity.

## Getting Started

### Prerequisites
- C++17 compiler or newer (e.g., g++, MSVC).

### Building
1. Clone the repository:
   ```bash
   git clone https://github.com/AliRaza-033/Personal_Finance_Manager_Cpp.git
   ```
2. Build using your favorite compiler:
   ```bash
   g++ Project.cpp -o finance_manager
   ```
3. Run the program:
   ```bash
   ./finance_manager
   ```

### File Structure

- `Project.cpp` – Main codebase.
- `user.txt` – Stores registered users and passwords.
- `records.txt` – Stores financial records for users.
- `output/` – Directory for output files (if used).
- `.vscode/` – Editor configuration.
- `readme.md` – Project documentation.

## Example Usage

On starting the program, you'll:
- Be greeted with a welcome message.
- Register or log in with credentials.
- Access your finance dashboard to add, view, or delete records and get financial advice.

## License

This project does not specify a license. Please contact the author for usage permissions.

## Author

Developed by [Ali Raza](https://github.com/AliRaza-033)

---

**Note:** This README was generated with limited code context. For more details, refer directly to [`Project.cpp`](https://github.com/AliRaza-033/Personal_Finance_Manager_Cpp/blob/Project/Project.cpp).
