////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2020 Ripose
//
// This file is part of Memento.
//
// Memento is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 2 of the License.
//
// Memento is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Memento.  If not, see <https://www.gnu.org/licenses/>.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef ENTRY_H
#define ENTRY_H

#include <QString>
#include <QList>

struct Entry
{
    Entry() : m_kanji(new QString),
              m_altkanji(new QString),
              m_kana(new QString), 
              m_altkana(new QString),
              m_descriptions(new QList<QList<QString>>),
              m_clozeBody(0),
              m_clozePrefix(0),
              m_clozeSuffix(0),
              m_sentence(0),
              m_exact(false) {}
    
    ~Entry()
    {
        delete m_kanji;
        delete m_altkanji;
        delete m_kana;
        delete m_altkana;
        delete m_descriptions;
        delete m_clozeBody;
        delete m_clozePrefix;
        delete m_clozeSuffix;
        delete m_sentence;
    }

    QString *m_kanji;
    QString *m_altkanji;
    QString *m_kana;
    QString *m_altkana;
    QList<QList<QString>> *m_descriptions;
    QString *m_clozeBody;
    QString *m_clozePrefix;
    QString *m_clozeSuffix;
    QString *m_sentence;
    bool m_exact;
} typedef Entry;

#endif // ENTRY_H