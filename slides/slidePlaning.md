**Slides and Script for Code Review Presentation**

---

### **Slide 1: Introduction**

**Title:** Code Review of Banking System Application

---

### **Script for Slide 1:**

Welcome everyone to this presentation on the code review of a simple banking system application developed in C++. We will delve into three main categories: Software Design and Engineering, Algorithms and Data Structures, and Databases. In each category, we'll discuss the existing code functionality, analyze it using relevant criteria, and propose practical enhancements.

---

### **Slide 2: Category One - Software Design and Engineering**

- **Existing Code Functionality:**
  - Implements a simple banking system in C++.
  - Features client management, password security, and main application flow.
  - Handles adding new clients, loading, and saving client data.

---

### **Script for Slide 2:**

In the first category, Software Design and Engineering, the code provides the foundation for a basic banking system. It allows for client management, including adding new clients and storing their account balances. Passwords are hashed using SHA256 for security. The main application flow involves prompting the user for credentials, adding the client with an initial balance, and saving the data.

---

### **Slide 3: Code Analysis and Findings**

- **Error Handling:** Lacks comprehensive error handling.
- **Input Validation:** User inputs are not validated.
- **Security Practices:** Passwords are hashed but not salted.
- **Incomplete Functionality:** Key functions are declared but not implemented.
- **Documentation:** Minimal comments and documentation.
- **Testing:** No unit tests or test cases.

---

### **Script for Slide 3:**

Upon analyzing the code, several issues emerge. There's a noticeable lack of error handling, which could lead to unhandled exceptions and crashes. Input validation is absent, making the system vulnerable to malicious inputs. While passwords are hashed, they aren't salted, posing security risks. Some essential functions like deposit and withdraw are declared but not implemented, limiting functionality. Additionally, the code lacks proper documentation and testing, which are crucial for maintainability and reliability.

---

### **Slide 4: Practical Enhancements**

- **Implement Comprehensive Error Handling**
- **Enhance Security Measures**
- **Complete Transaction Functions**
- **Add Input Validation**
- **Improve Documentation**
- **Implement Testing**

---

### **Script for Slide 4:**

To address these issues, I propose several enhancements. First, we should implement comprehensive error handling to make the application robust. Enhancing security measures, such as adding password salting and using a more secure hashing algorithm, is essential. Completing the transaction functions will provide the necessary functionality. Adding input validation will protect against injection attacks. Improving documentation and implementing testing will ensure the code is maintainable and functions as expected. These enhancements demonstrate skills in secure coding, error handling, and software engineering principles, aligning with our course outcomes.

---

### **Slide 5: Category Two - Algorithms and Data Structures**

- **Existing Code Functionality:**
  - Uses standard data structures: `unordered_map`, `Client` struct.
  - Password hashing with SHA256.
  - Manages balances with dollars and cents.

---

### **Script for Slide 5:**

Moving on to Algorithms and Data Structures, the code utilizes standard C++ data structures. An `unordered_map` is used for efficient client retrieval, and a `Client` struct holds user credentials and account balances. Passwords are hashed using SHA256, and balances are managed with separate variables for dollars and cents.

---

### **Slide 6: Code Analysis and Findings**

- **Data Type Limitations:** `uint8_t` for cents limits value to 255.
- **Precision Issues:** Separation of dollars and cents can cause errors.
- **Password Hashing Algorithm:** Lacks salting, vulnerable to attacks.
- **Inefficient Balance Handling:** Carry-over logic can be optimized.

---

### **Script for Slide 6:**

Analyzing the code reveals several weaknesses. Using `uint8_t` for cents can lead to overflow issues since it only supports values up to 255. Separating dollars and cents may introduce calculation errors, and handling money as floating-point numbers is risky due to precision errors. The password hashing algorithm is not secure enough without salting. Additionally, the balance handling logic for carry-over in cents to dollars is inefficient and could be improved.

---

### **Slide 7: Practical Enhancements**

- **Use Appropriate Data Types**
- **Improve Password Security**
- **Optimize Algorithms**
- **Implement Data Validation**

---

### **Script for Slide 7:**

To enhance the code, we should use appropriate data types, such as representing monetary values using a single integer or a high-precision decimal type to avoid overflow and precision issues. Improving password security by switching to algorithms like bcrypt or Argon2 with salting will protect against attacks. Optimizing the balance calculation logic will improve efficiency. Implementing data validation ensures arithmetic operations are safe. These changes demonstrate skills in selecting appropriate data structures and implementing secure algorithms, aligning with our course outcomes.

---

### **Slide 8: Category Three - Databases**

- **Existing Code Functionality:**
  - Uses a JSON file for data storage.
  - Reads and writes client data for persistence.

---

### **Script for Slide 8:**

In the category of Databases, the application currently relies on a JSON file to store and retrieve client data. It reads from the file during initialization and writes back to it upon changes, which allows for data persistence across sessions.

---

### **Slide 9: Code Analysis and Findings**

- **Scalability Issues:** JSON file isn't scalable for many clients.
- **Data Integrity and Concurrency:** No concurrency control.
- **Security Concerns:** Sensitive data stored in plain text.
- **Error Handling:** Insufficient for file operations.

---

### **Script for Slide 9:**

However, this approach presents several problems. Storing data in a JSON file doesn't scale well as the number of clients grows, leading to performance degradation. There's a lack of concurrency control, which could result in data corruption if multiple instances access the file simultaneously. Security is a major concern since sensitive data is stored in plain text. Additionally, error handling for file operations is insufficient, risking data loss.

---

### **Slide 10: Practical Enhancements**

- **Integrate a Database System**
- **Implement ORM**
- **Enhance Security**
- **Add Transaction Support**

---

### **Script for Slide 10:**

To improve the system, we should integrate a proper database system like SQLite or MySQL, which offers better scalability, security, and data integrity. Implementing an ORM will streamline database interactions. Enhancing security by encrypting sensitive data and securing database access is crucial. Adding transaction support will ensure data consistency. These enhancements will demonstrate skills in database design and secure data handling, aligning with our course outcomes.

---

### **Slide 11: Conclusion**

- **Summarized Findings and Enhancements**
- **Alignment with Course Outcomes**
- **Skills Demonstrated:**
  - Secure Coding Practices
  - Error Handling
  - Software Engineering Principles
  - Algorithms and Data Structures
  - Database Design and Management

---

### **Script for Slide 11:**

In conclusion, the code review highlighted several areas for improvement across software design, algorithms, and databases. By implementing the proposed enhancements, we align the application with best practices and course outcomes. The enhancements will demonstrate our skills in secure coding, error handling, software engineering principles, algorithm optimization, and database management.

---

### **Slide 12: Q&A**

**Thank you for your attention. Any questions?**

---

### **Script for Slide 12:**

Thank you for your time and attention. I'd be happy to answer any questions you might have.

---
