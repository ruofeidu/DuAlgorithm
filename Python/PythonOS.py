# multiprocessing
import os

print('Process (%s) start...' % os.getpid())
# Only works on Unix/Linux/Mac:
# pid = os.fork()
# if pid == 0:
#   print('I am child process (%s) and my parent is %s.' % (os.getpid(), os.getppid()))
# else:
#   print('I (%s) just created a child process (%s).' % (os.getpid(), pid))

from multiprocessing import Pool
import os, time, random


def long_time_task(name):
    print('Run task %s (%s)...' % (name, os.getpid()))
    start = time.time()
    time.sleep(random.random() * 3)
    end = time.time()
    print('Task %s runs %0.2f seconds.' % (name, (end - start)))


from multiprocessing import Process, Queue
import os, time, random


# write process
def write(q):
    print('Process to write: %s' % os.getpid())
    for value in ['A', 'B', 'C']:
        print('Put %s to queue...' % value)
        q.put(value)
        time.sleep(random.random())


# read process
def read(q):
    print('Process to read: %s' % os.getpid())
    while True:
        value = q.get(True)
        print('Get %s from queue.' % value)


if __name__ == '__main__':
    print('Parent process %s.' % os.getpid())
    p = Pool(4)
    for i in range(5):
        p.apply_async(long_time_task, args=(i,))
    print('Waiting for all subprocesses done...')
    p.close()
    p.join()
    print('All subprocesses done.')

    # the root creates a queue and subprocesses:
    q = Queue()
    pw = Process(target=write, args=(q,))
    pr = Process(target=read, args=(q,))
    # start subprocess pw, write
    pw.start()
    # start subprocess pr, read
    pr.start()
    # wait until pw ends
    pw.join()
    # force terminate pr, since it's a dead-loop process
    pr.terminate()

