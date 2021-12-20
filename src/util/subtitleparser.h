////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2021 Ripose
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

#ifndef SUBTITLEPARSER_H
#define SUBTITLEPARSER_H

#include <QList>
#include <QRegularExpression>
#include <QSet>
#include <QString>

class QFile;

/**
 * Information about a subtitle.
 */
struct SubtitleInfo
{
    /* The text of the subtitle */
    QString text;

    /* The start time of the subtitle in seconds */
    double start;

    /* The end time of the subtitle in seconds */
    double end;

    SubtitleInfo &operator=(const SubtitleInfo &rhs)
    {
        text = rhs.text;
        start = rhs.start;
        end = rhs.end;

        return *this;
    }
} typedef SubtitleInfo;

/**
 * Object for parsing subtitles of various formats.
 */
class SubtitleParser
{
public:
    SubtitleParser();

    /**
     * Parses the subtitles at the given path if possible and returns text,
     * start, and end times for each subtitle.
     * @param path     The path to the subtitle.
     * @param compress If true, subtitles are merged if they overlap in time.
     *                 This option mimics how mpv's 'sub-text' property handles
     *                 subtitles whose timecodes overlap.
     * @return A list of SubtitleInfos extracted from the subtitle file.
     */
    QList<SubtitleInfo> parseSubtitles(
        const QString &path,
        bool compress = false) const;

private:
    /**
     * Parses ASS subtitles.
     * @param      file The file containing the raw ass.
     * @param[out] out  The list the resulting SubtitleInfos are saved to.
     * @return true on success, false on error.
     */
    bool parseASS(QFile &file, QList<SubtitleInfo> &out) const;

    /**
     * Parses SRT subtitles.
     * @param      file The file containing the raw srt.
     * @param[out] out  The list the resulting SubtitleInfos are saved to.
     * @return true on success, false on error.
     */
    bool parseSRT(QFile &file, QList<SubtitleInfo> &out) const;

    /**
     * Parses VTT subtitles.
     * @param      file The file containing the raw vtt.
     * @param[out] out  The list the resulting SubtitleInfos are saved to.
     * @return true on success, false on error.
     */
    bool parseVTT(QFile &file, QList<SubtitleInfo> &out) const;

    /**
     * Converts a timecode of the format HH:MM:SS,MsMsMs
     * @param      timecode The timecode string.
     * @param[out] ok       Set to true on success, false on error.
     * @return The timecode in seconds.
     */
    double timecodeToDouble(const QString &timecode, bool *ok = nullptr) const;

    /**
     * Takes a list of SubtitleInfos and merges subtitles that overlap in time.
     * @param subtitles The list of subtitles to compress.
     * @return The compressed list of subtitles.
     */
    QList<SubtitleInfo> compressSubtitles(
        const QList<SubtitleInfo> &subtitles) const;

    /* The regular expression for splitting timecodes */
    QRegularExpression m_timecodeSplitter;

    /* Removes ASS styling overrides */
    QRegularExpression m_assFilter;

    /* Adds newlines to ASS subtitles */
    QRegularExpression m_assNewLineReplacer;

    /* The regular expression for removing SRT formatting */
    QRegularExpression m_srtFilter;

    /* Removes everything between angle braces */
    QRegularExpression m_angleBraceCleaner;

    /* A set of special VTT sections */
    QSet<QString> m_vttSections;
};

#endif // SUBTITLEPARSER_H