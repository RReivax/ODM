/**
 * Copyright 2017 Gauthier Leonard, Xavier Hermand, Robin Dade, Oscar Blazejewski, Arnaud Petitcol
 * This file is part of Open Drone Monitoring.
 * Open Drone Monitoring is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Open Drone Monitoring is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
 * You should have received a copy of the GNU Lesser General Public License along with Open Drone Monitoring. If not, see <http://www.gnu.org/licenses/>.
*/
#include "qjsonstack.h"

QJsonStack::QJsonStack(QObject *parent) : QObject(parent)
{

}
QJsonStack::QJsonStack(QJsonStack const &init) : QObject(0)
{
    *this = init;
}
bool QJsonStack::isEmptyEmitSignal()
{
    if(m_jsonstack.isEmpty())
    {
        emit StackEmpty();
        return true;
    }
    else
        return false;
}
QStack<value_type>& QJsonStack::toQStack()
{
    return m_jsonstack;
}
void QJsonStack::push(const value_type &newValue)
{
    m_jsonstack.push(newValue);
}
value_type QJsonStack::pop()
{
    return m_jsonstack.pop();
}
int QJsonStack::size() const
{
    return m_jsonstack.size();
}
void QJsonStack::operator=(QJsonStack const& b)
{
    m_jsonstack=b.m_jsonstack;
}
