# Personal Organizer - Detailed Code Implementation Guide

A comprehensive guide to understanding the codebase of our Personal Organizer application, with special focus on the QSettings-based database implementation.

## Core Database Implementation 🔐

### QSettings Database System (`database.h`, `database.cpp`)

The application uses Qt's QSettings for data persistence, providing a simple yet powerful way to store application data. Here's a detailed breakdown:

```cpp
class Database : public QObject {
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr);
    bool addUser(const QString &username, const QString &password);
    bool validateUser(const QString &username, const QString &password);
    void saveUsers();
    void loadUsers();

private:
    QSettings* settings;
    QMap<QString, QByteArray> users; // username -> hashed password
};
```

#### Key Implementation Details:

1. **QSettings Initialization**:
```cpp
Database::Database(QObject *parent)
    : QObject(parent)
    , settings(new QSettings("PersonalOrganizerDB", "PersonalOrganizer", this))
{
    loadUsers();
}
```
- Uses organization name "PersonalOrganizerDB" and application name "PersonalOrganizer"
- Automatically handles data storage location based on OS
- Windows: Registry or INI files in AppData
- Linux: INI files in ~/.config
- macOS: Property list files in ~/Library/Preferences

2. **Secure Password Storage**:
```cpp
bool Database::addUser(const QString &username, const QString &password) {
    // Hash password using SHA-256
    QByteArray hashedPassword = QCryptographicHash::hash(
        password.toUtf8(),
        QCryptographicHash::Sha256
    );
    users[username] = hashedPassword;
    saveUsers();
    return true;
}
```
- Uses SHA-256 for password hashing
- Stores only hashed passwords, never plain text
- Automatically handles data persistence

3. **Data Persistence Implementation**:
```cpp
void Database::saveUsers() {
    settings->beginGroup("Users");
    settings->remove(""); // Clear existing users
    
    // Save each user with hex-encoded password hash
    for (auto it = users.constBegin(); it != users.constEnd(); ++it) {
        settings->setValue(it.key(), it.value().toHex());
    }
    
    settings->endGroup();
    settings->sync(); // Ensure data is written to disk
}
```
- Uses hierarchical data storage with groups
- Converts binary data to hex for storage
- Ensures immediate disk write with sync()

4. **Data Loading Implementation**:
```cpp
void Database::loadUsers() {
    settings->beginGroup("Users");
    QStringList usernames = settings->childKeys();
    
    for (const QString &username : usernames) {
        QByteArray hashedPassword = QByteArray::fromHex(
            settings->value(username).toByteArray()
        );
        users[username] = hashedPassword;
    }
    
    settings->endGroup();
}
```
- Automatically loads data on startup
- Handles hex-to-binary conversion
- Maintains in-memory user map

## Financial Management System 💰

### Transaction Management (`transaction.h`, `transaction.cpp`)

```cpp
class Transaction {
public:
    enum class Type { Income, Expense };
    QString description;
    double amount;
    QDate date;
    QString category;
    Type type;
};
```

#### Implementation Details:

1. **Transaction Storage**:
```cpp
void MainWindow::saveTransactions() {
    settings->beginGroup("Transactions");
    settings->remove("");
    
    for (int i = 0; i < transactions.size(); ++i) {
        settings->beginGroup(QString("Transaction_%1").arg(i));
        settings->setValue("description", transactions[i].description);
        settings->setValue("amount", transactions[i].amount);
        settings->setValue("date", transactions[i].date);
        settings->setValue("category", transactions[i].category);
        settings->setValue("type", static_cast<int>(transactions[i].type));
        settings->endGroup();
    }
    
    settings->endGroup();
    settings->sync();
}
```

2. **Budget Management**:
```cpp
void MainWindow::saveBudgets() {
    settings->beginGroup("Budgets");
    for (auto it = budgets.constBegin(); it != budgets.constEnd(); ++it) {
        settings->setValue(it.key(), it.value());
    }
    settings->endGroup();
    settings->sync();
}
```

## Academic Management System 📚

### Academic Item Management (`academicitem.h`, `academicitem.cpp`)

```cpp
class AcademicItem {
public:
    enum class Type { Lecture, Deadline };
    QString title;
    QDateTime dateTime;
    QString description;
    Type type;
    int duration; // in minutes
};
```

#### Implementation Details:

1. **Academic Schedule Storage**:
```cpp
void MainWindow::saveAcademicItems() {
    settings->beginGroup("AcademicItems");
    settings->remove("");
    
    for (int i = 0; i < academicItems.size(); ++i) {
        settings->beginGroup(QString("Item_%1").arg(i));
        settings->setValue("title", academicItems[i].title);
        settings->setValue("dateTime", academicItems[i].dateTime);
        settings->setValue("description", academicItems[i].description);
        settings->setValue("type", static_cast<int>(academicItems[i].type));
        settings->setValue("duration", academicItems[i].duration);
        settings->endGroup();
    }
    
    settings->endGroup();
    settings->sync();
}
```

## Data Organization Structure 📁

The application organizes data hierarchically in QSettings:

```
PersonalOrganizerDB/
├── Users/
│   ├── username1 -> hashed_password1
│   ├── username2 -> hashed_password2
│   └── ...
├── Transactions/
│   ├── Transaction_0/
│   │   ├── description
│   │   ├── amount
│   │   ├── date
│   │   ├── category
│   │   └── type
│   └── ...
├── Budgets/
│   ├── category1 -> amount1
│   ├── category2 -> amount2
│   └── ...
└── AcademicItems/
    ├── Item_0/
    │   ├── title
    │   ├── dateTime
    │   ├── description
    │   ├── type
    │   └── duration
    └── ...
```

## Key Features of QSettings Implementation 🔑

1. **Automatic Data Persistence**:
   - No need for explicit file handling
   - Data automatically saved to appropriate OS location
   - Handles data type conversion automatically

2. **Thread Safety**:
   - QSettings is thread-safe
   - Multiple instances can access same data
   - Automatic synchronization between instances

3. **Platform Independence**:
   - Works across Windows, Linux, and macOS
   - Handles platform-specific storage locations
   - Maintains consistent data format

4. **Data Security**:
   - Passwords stored as hashes
   - Data stored in user-specific locations
   - Automatic data backup by OS

## Best Practices Implemented 🏆

1. **Data Organization**:
   - Clear hierarchical structure
   - Logical grouping of related data
   - Consistent naming conventions

2. **Error Handling**:
   - Graceful handling of missing data
   - Validation of input data
   - Backup of critical data

3. **Performance Optimization**:
   - In-memory caching of frequently accessed data
   - Batch operations for multiple items
   - Efficient data structure usage

## Future Improvements 🚀

1. **Database Enhancements**:
   - Implement data encryption
   - Add data compression
   - Implement data versioning

2. **Performance Optimizations**:
   - Implement data caching
   - Add batch operations
   - Optimize data loading

## License 📄

MIT License - Feel free to use and modify the code!

---

This implementation guide provides a detailed overview of the QSettings-based database system and other core components. For specific implementation details, refer to the respective source files.
