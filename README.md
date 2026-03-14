# Network Registry Management System

## 🌐 Project Overview
This repository contains a specialized **Network Registry Management System** implemented in C. The system is designed to handle device registrations (including MAC addresses and user status) using dynamic memory management and structured data processing.

It demonstrates a "CRUD-lite" approach: **C**reating new records, **R**eading from flat files, and **U**pdating the registry state in-memory.

## 🏗 Key Engineering Concepts
- **Dynamic Memory Management:** Efficient use of `malloc` and `realloc` to handle variable-sized datasets without memory waste.
- **File I/O & Parsing:** Custom implementation for loading and parsing structured text data, including header-skipping logic and cursor rewinding.
- **Data Structures:** Utilization of `struct` to encapsulate complex entities (Registration ID, Name, MAC Address, etc.).
- **Algorithm Implementation:** A custom **Bubble Sort** implementation for organizing data by Year or Surname.
- **Input Validation:** Robust validation for technical strings, such as ensuring MAC addresses follow the standard `XX:XX:XX:XX:XX:XX` format.

## 🛠 Features
- **Registration Statistics:** Real-time calculation of "Approved", "Blocked", and "Declined" status distributions.
- **Automated ID Generation:** Sequential registration ID assignment to ensure data integrity.
- **Sorting Engine:** Dual-mode sorting capability for large datasets.

## 🚀 Execution Guide
1. **Compilation:**
   ```bash
   gcc main.c -o network_registry
   ```
2. **Setup:** Ensure you have a .txt data file (e.g., data.txt) in the directory with the following header:
REGID NAME SURNAME STATUS YEAR DEVICEMACADDRESS
3. **Run:**
   ```bash
   ./network_registry
   ```

Developed by Ahmet Onur Taşgüzen as part of the METU Computer Engineering curriculum, focusing on System Programming foundations.
