
# Test Cases – Printer Job Management System

## Project Details
- Course: CSS2281
- Language: C
- Data Structure: Circular Queue
- Testing type: Functional testing

## Test Case 1: Display an Empty Queue
**Input:** Select option 2 immediately after starting the program.  
**Expected result:** "No pending print jobs."

## Test Case 2: Add a Print Job
**Input:**
- Document: Report.pdf
- User: Student1
- Pages: 12

**Expected result:** Job is added successfully and assigned an ID.

## Test Case 3: Display Pending Jobs
**Input:** Add two or more jobs and select option 2.  
**Expected result:** All pending jobs appear in submission order.

## Test Case 4: Process the Next Job
**Input:** Add Job A and Job B, then select option 3.  
**Expected result:** Job A is processed first, and Job B remains pending.

## Test Case 5: Cancel a Pending Job
**Input:** Add multiple jobs and cancel one using its job ID.  
**Expected result:** The selected job is removed and the order of other jobs is preserved.

## Test Case 6: Search for a Completed Job
**Input:** Process a job and search using its ID.  
**Expected result:** The job is found in completed history.

## Test Case 7: Search for an Invalid Job ID
**Input:** Enter an ID that does not exist.  
**Expected result:** The program displays a job-not-found message.

## Test Case 8: Process an Empty Queue
**Input:** Select option 3 when no jobs are pending.  
**Expected result:** "No jobs available to print."

## Test Case 9: Invalid Menu Input
**Input:** Enter letters instead of a menu number.  
**Expected result:** The program displays an invalid-input message and asks again.

## Test Case 10: Queue Capacity
**Input:** Fill the pending queue with 100 jobs, then attempt to add another job.  
**Expected result:** The program rejects the additional job because the queue is full.

## Test Results
Run each test case and record the actual result.

| Test Case | Actual Result | Status |
|---|---|---|
| 1 | To be recorded | Pending |
| 2 | To be recorded | Pending |
| 3 | To be recorded | Pending |
| 4 | To be recorded | Pending |
| 5 | To be recorded | Pending |
| 6 | To be recorded | Pending |
| 7 | To be recorded | Pending |
| 8 | To be recorded | Pending |
| 9 | To be recorded | Pending |
| 10 | To be recorded | Pending |
