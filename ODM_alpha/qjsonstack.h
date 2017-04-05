/**
 * Copyright 2017 Gauthier Leonard, Xavier Hermand, Robin Dade, Oscar Blazejewski, Arnaud Petitcol
 * This file is part of Open Drone Monitoring.
 * Open Drone Monitoring is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Open Drone Monitoring is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
 * You should have received a copy of the GNU Lesser General Public License along with Open Drone Monitoring. If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef QJSONSTACK_H
#define QJSONSTACK_H

#include <QtCore>
#include <QStack>
#include <QDebug>

#define value_type QJsonObject

/**
 * @class QJsonStack
 * @brief The QJsonStack class
 * 		is an overload of a QStack<QJsonObject> which send a signal when empty
 * 
 * The QJsonStack is a QObject that will send a signal if it is empty when you check for it.
 * You can go back to a classic QStack<QJsonObject> by calling the toQStack methode
 * 
 */
class QJsonStack : public QObject
{
    Q_OBJECT
public:
    /** @fn QJsonStack::QJsonStack(QObject *parent)
     *  @brief Default constructor
     * 
     *  Doesn't initialise anything except for the parent of the QObject. So the stack will be initialise by the QStack<QJsonObject> default constructor
     */
    explicit QJsonStack(QObject *parent = 0);
    /** @fn QJsonStack::QJsonStack(QJsonStack const &init)
     *  @brief Copy constructor
     *
     * Use the deep copy operator for the stack. The parent of the QObject is set to NULL.
     */
    QJsonStack(const QJsonStack &init);
    /** @fn bool QJsonStack::isEmptyEmitSignal()
     *  @brief Return if the stack is empty and send a signal if it is
     *  @return boolean  same as QStack<QJsonObject>::isEmpty()
     *
     */
    bool isEmptyEmitSignal();
    /** @fn QStack<value_type>& QJsonStack::toQStack()
     *  @brief To comme back to a classic QStack<QJsonObject>
     *  @return QStack<QJsonObject> : return the hidden 
     */
    QStack<value_type>& toQStack();
    /** @fn value_type QJsonStack::pop()
     *  @brief Same as QStack<QJsonObject>::pop()
     *  @return QJsonObject : return the Json at the top of the stack 
     */
    value_type pop();
    /** @fn int QJsonStack::size() const
     *  @brief Same as QStack<QJsonObject>::size()
     *  @return Int : return the depth of the stack 
     */
    int size() const;
    /** @fn void QJsonStack::operator=(QJsonStack const& b)
     *  @brief Deep copy of the stack
     * 
     *  Use the deep copy operator of QStack<QJsonObject>
     */
    void operator=(QJsonStack const& b);
signals:
    void StackEmpty();
public slots:
    void push(const value_type &newValue);
private:
       QStack<value_type> m_jsonstack;
};

#endif // QJSONSTACK_H
