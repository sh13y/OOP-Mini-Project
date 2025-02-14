#ifndef ACADEMICITEM_H
#define ACADEMICITEM_H

#include <QString>
#include <QDateTime>

// Class to represent academic items (lectures and deadlines)
class AcademicItem {
public:
    // Enum to distinguish between different types of academic items
    enum Type {
        Lecture,    // Regular lecture with duration
        Deadline    // Assignment or exam deadline
    };

    // Constructor to create a new academic item
    // Parameters:
    //   type: Type of item (lecture/deadline)
    //   title: Name or title of the item
    //   description: Detailed description
    //   dateTime: When the lecture/deadline occurs
    //   durationMinutes: Length of lecture (only used for lectures)
    AcademicItem(Type type, const QString &title, const QString &description,
                 const QDateTime &dateTime, int durationMinutes = 0);

    // Getter methods to access private member variables
    Type type() const { return m_type; }
    QString title() const { return m_title; }
    QString description() const { return m_description; }
    QDateTime dateTime() const { return m_dateTime; }
    int durationMinutes() const { return m_durationMinutes; }

    // Returns true if deadline is within next 24 hours
    bool isDeadlineApproaching() const;

private:
    Type m_type;                // Type of academic item
    QString m_title;            // Title/name of the item
    QString m_description;      // Detailed description
    QDateTime m_dateTime;       // When the item occurs
    int m_durationMinutes;      // Duration (for lectures only)
};

#endif // ACADEMICITEM_H 