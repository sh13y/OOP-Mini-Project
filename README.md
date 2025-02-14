# Personal Finance & Academic Organizer

## Table of Contents
- [Overview](#overview)
- [Key Features](#key-features)
- [Technical Details](#technical-details)
- [Setup Instructions](#setup-instructions)
- [Design Decisions](#design-decisions)
- [Future Enhancements](#future-enhancements)
- [Project Structure](#project-structure)
- [Code Style](#code-style)
- [Testing](#testing)
- [Known Issues](#known-issues)
- [Contributing](#contributing)
- [License](#license)
- [Authors](#authors)
- [Acknowledgments](#acknowledgments)
- [TODO Checklist](#todo-checklist)

## Overview
A Qt-based desktop application designed to help students manage both their finances and academic schedules. The application features a clean, modern interface with a custom color palette inspired by professional design principles. 
> **Note:** This app won't do your homework, but it will help you afford the coffee you need to stay awake while doing it!

## Key Features

### 1. User Authentication
- Secure login system
- User registration with password validation
- Data persistence between sessions
> **Warning:** Forgetting your password may lead to existential crises. 

### 2. Financial Management
- Track both income and expenses
- Categorized transactions
- Monthly budget setting and tracking
- Detailed financial reports
- Visual representation through charts
- Multiple income sources (Job, Scholarships, Allowance, Student Aid)
- Customizable expense categories
> **Fun Fact:** If you can't find your wallet, it's probably hiding from your budget!

### 3. Academic Schedule Management
- Lecture schedule tracking
- Assignment deadline management
- Automatic deadline alerts
- Duration tracking for lectures
- Detailed view of academic commitments
> **Reminder:** Procrastination is not a valid time management strategy!

### 4. User Interface
- Modern, minimalist design
- Custom color palette:
  - Rose Taupe (#9F6571) - Primary color
  - Black (#000000) - Text
  - Sage (#BBB68C) - Secondary elements
  - Eggshell (#F0EEDC) - Background
  - Rose Pompadour (#F27D97) - Accents

## Technical Details

### Architecture
- Language: C++ 17
- Framework: Qt 6
- Database: Local file-based storage using QSettings
- UI: Qt Widgets with custom styling

### Key Components
1. **User Management**
   - `LoginWindow`: Handles user login.
   - `RegisterDialog`: Manages user registration.
   - `Database`: Handles data storage and retrieval.

2. **Financial Module**
   - `Transaction`: Manages financial transactions.
   - `TransactionDialog`: Dialog for adding/editing transactions.
   - Report generation and chart visualization.

3. **Academic Module**
   - `AcademicItem`: Represents academic commitments.
   - `AcademicDialog`: Dialog for adding/editing academic items.

## Setup Instructions

### Prerequisites
- Qt 6.8.2 or later
- C++ compiler with C++17 support
- Qt Creator IDE (recommended)

### Building the Project
1. Clone the repository.
2. Open `PersonalOrganizer.pro` in Qt Creator.
3. Configure the project with the appropriate kit.
4. Build and run.

## Design Decisions

### 1. User Interface
- Tab-based main interface for clear separation of functions.
- Consistent color scheme throughout.
- Responsive layout adapting to window size.
- Modern flat design with subtle animations.

### 2. Data Management
- Local storage for simplicity and portability.
- Real-time data updates.
- Automatic data persistence.

### 3. Security
- Basic password protection.
- Data validation at entry points.
- Error handling and user feedback.

## Future Enhancements
1. Cloud synchronization.
2. Multiple currency support.
3. Export functionality for reports.
4. Advanced budget analysis tools.
5. Calendar integration.
6. Mobile companion app.
> **Coming Soon:** An AI that reminds you to stop binge-watching and start studying!

## Project Structure 

```
PersonalOrganizer/
├── source/
│   ├── main.cpp                # Entry point of the application
│   ├── loginwindow.cpp         # Handles user login
│   ├── mainwindow.cpp          # Main application window
│   ├── transaction.cpp         # Manages financial transactions
│   └── academicitem.cpp        # Represents academic commitments
├── headers/
│   ├── loginwindow.h           # Header for login window
│   ├── mainwindow.h            # Header for main window
│   ├── transaction.h           # Header for transaction management
│   └── academicitem.h          # Header for academic item management
├── forms/
│   ├── loginwindow.ui          # UI for login window
│   ├── mainwindow.ui           # UI for main window
│   └── transactiondialog.ui    # UI for transaction dialog
├── resources/
│   └── app_icon.ico            # Application icon
└── PersonalOrganizer.pro       # Qt project file
```

## Code Style
- Clear class hierarchies
- Consistent naming conventions
- Comprehensive error handling
- Detailed comments and documentation

## Testing
- Manual testing of all features
- Edge case handling
- Input validation testing
- UI responsiveness testing

## Known Issues
- None currently reported

## Contributing
1. Fork the repository
2. Create feature branch
3. Commit changes
4. Push to branch
5. Create Pull Request

## License
MIT License

## Authors
sh13y

## Acknowledgments
- Qt Documentation
- C++ Best Practices
- Modern UI Design Principles

## TODO Checklist
### Requirements
- [x] **User Account System**: Each user can create an account with a username and password. Data is saved in a file or database.
- [x] **Income and Expense Tracker**: Users can add income sources (job, allowance from parents, scholarships, student aid) and expenses. Each entry will have a date, description, category (food, entertainment, traveling, clothing, education equipment, university fees), and amount.
- [x] **Category-Based Budgeting**: Users can set monthly target budgets for different categories (e.g. Rs. 2000 for entertainment). The program alerts when a budget is exceeded.
- [x] **Financial Reports**: Generate monthly reports showing total income, total expenses, and savings. Graphical representation of expenses by category using charts (bar graph). This should show the current status on each day with how much have been spent and how much remains.
- [x] **Academic Schedule**: Users can add their weekly lecture schedule and set the time duration for it. Users should be able to include important dates such as assignment deadlines and the program should give alerts when nearing a deadline.
- [x] **GUI Component**: Use a C++ GUI framework like Qt or .Net to create a user-friendly interface. Display income/expense forms, graphs, and reports. Buttons for adding income, expenses, generating reports, etc.
- [x] **Data Persistence**: Can use a DBMS (for bonus marks) or file handling (CSV or text files) to store and retrieve user data. Using JSON is also accepted. Optional: Implement basic encryption for storing sensitive data like account details (for bonus marks).

