/*
 *  Copyright (c) 2017 Dmitry Kazakov <dimula73@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef KISRUNNABLESTROKEJOBUTILS_H
#define KISRUNNABLESTROKEJOBUTILS_H

#include <QVector>

#include "kis_stroke_job_strategy.h"
#include "KisRunnableStrokeJobData.h"

namespace KritaUtils
{

template <typename Func>
void addJobSequential(QVector<KisRunnableStrokeJobData*> &jobs, Func func) {
    jobs.append(new KisRunnableStrokeJobData(func, KisStrokeJobData::SEQUENTIAL));
}

template <typename Func>
void addJobConcurrent(QVector<KisRunnableStrokeJobData*> &jobs, Func func) {
    jobs.append(new KisRunnableStrokeJobData(func, KisStrokeJobData::CONCURRENT));
}

template <typename Func>
void addJobBarrier(QVector<KisRunnableStrokeJobData*> &jobs, Func func) {
    jobs.append(new KisRunnableStrokeJobData(func, KisStrokeJobData::BARRIER));
}

template <typename Func>
void addJobUniquelyCuncurrent(QVector<KisRunnableStrokeJobData*> &jobs, Func func) {
    jobs.append(new KisRunnableStrokeJobData(func, KisStrokeJobData::UNIQUELY_CONCURRENT));
}

}

#endif // KISRUNNABLESTROKEJOBUTILS_H