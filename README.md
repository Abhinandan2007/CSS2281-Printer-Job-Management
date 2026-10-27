
# Printer Job Management System

**Course:** CSS2281 – Problem-Based Activity  
**Language:** C  
**Data Structure:** Circular Queue

## 1. Project Description
This project simulates a printer management system that manages print requests using a queue. Jobs are processed in First In, First Out (FIFO) order.

## 2. Objectives
- Understand queue operations.
- Implement enqueue and dequeue.
- Manage pending print jobs.
- Search and cancel jobs.
- Maintain completed job history.

## 3. Features
1. Add a print job
2. Display pending jobs
3. Process the next job
4. Cancel a pending job
5. Search for a job
6. Display the next job
7. Calculate pending pages
8. View completed job history

## 4. Data Structure
The program uses a circular queue implemented using an array of structures.

- Enqueue: O(1)
- Dequeue: O(1)
- Search: O(n)
- Cancellation: O(n)

## 5. How to Run

Compile using Clang:

    clang -std=c11 -Wall -Wextra -pedantic printer_management.c -o printer_management

Run:

    ./printer_management

## 6. Testing
Test the program with multiple jobs, FIFO processing, cancellation, search, empty-queue handling, and invalid inputs.

## 7. Limitations
- This is a simulation, not a physical printer driver.
- Data is stored in memory and is lost when the program exits.
- The pending queue supports up to 100 jobs.

## 8. Team Members
1. Name: ABHINANDAN B DHOTRE | Register No.: 20251ECE0208
2. Name: TILAK H G | Register No.: 20251ECE0218
3. Name:  LOHITH M GOWDA | Register No.: 20251ECE0220
4. Name: VANDANA M S | Register No.: 20251ECE0185
5. Name: LAVANYA P S | Register No.: 20251ECE0211

## 9. Conclusion
This project demonstrates how a circular queue can manage print requests efficiently using FIFO processing.
