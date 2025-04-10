
# 💊 PharmaChain: Blockchain-Based Medicine Distribution System

PharmaChain is a simple yet powerful C++ project that simulates a blockchain-based distribution system for tracking and verifying medicine batches from manufacturer to customer. It ensures product authenticity, improves traceability, and minimizes the risk of counterfeit drugs.

---

## 🚀 Features

- 👨‍🔬 **Manufacturer Role**  
  - Create new medicine batches.
  - Assign delivery routes to pharmacies using:
    - Prim’s Algorithm (Single Truck)
    - Dijkstra’s Algorithm (Multiple Trucks)
  - Track delivery progress across pharmacies.

- 💊 **Pharmacist Role**  
  - Check incoming batches.
  - Verify batch validity using blockchain.
  - Confirm delivery reception in sequential order.

- 👤 **Customer Role**  
  - Verify medicine authenticity using batch info on packaging.

- 🔗 **Blockchain Core**  
  - Each batch is recorded as a block with a unique hash.
  - Tracks status updates and delivery path.
  - Detects tampering using hash re-validation.

---

## 📂 Project Structure

```
.
├── main.cpp              # Application flow for all roles
├── blockchain.cpp        # Blockchain and Block structure
├── manufacturer.cpp      # Manufacturer functionalities
├── pharmacist.cpp        # Pharmacist functionalities
├── customer.cpp          # Customer interaction and verification
└── README.md             # Project documentation
```

---

## 🧪 How It Works

1. **Manufacturer** creates a batch and assigns delivery paths.
2. **Pharmacies** receive the batch in sequence and confirm delivery.
3. **Customers** check the batch info and verify authenticity using blockchain hash matching.

---

## 🛠 Tech Stack

- Language: **C++**
- Data Structures: Linked List, Map, Vector,
- Algorithms: **Hashing**, **Prim's MST**, **Dijkstra's Shortest Path**
- Concepts: Blockchain, Authentication, Supply Chain Tracking

---

## 🧑‍💻 How to Run

1. Make sure all `.cpp` files are in the same directory.
2. Compile using a C++ compiler:
   ```bash
   g++ main.cpp -o pharmachain
   ./pharmachain
   ```
3. Follow the on-screen menu to simulate roles.

---

## 📌 Future Improvements

- Add deliveryGraph with actual Prim's & Dijkstra's algorithm logic.
- Replace CLI with a GUI or Web interface.
- Add timestamping and cryptographic hashing for better security.
- Connect to a real blockchain or distributed ledger.

---

## 📸 Preview (Sample Flow)

```bash
👤 Select Role:
1. Manufacturer
2. Pharmacist
3. Customer

[Manufacturer]
- Enter batch details
- Set delivery path: A → B → C
- Blockchain updated ✅

[Pharmacist]
- Check incoming batch 📦
- Verified and confirmed ✅

[Customer]
- Scan and enter batch info
- ✅ Medicine is authentic
```

---

## 🤝 Contributions

Pull requests, issues, and suggestions are welcome. Let's make medicine distribution safer together!

---

## 📝 License

This project is for educational purposes. Customize and extend as per your use-case.
