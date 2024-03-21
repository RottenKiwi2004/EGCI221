function validEdge(str1: string, str2: string): boolean {
    if (str1.length != str2.length) return false;
    let count: number = 0;
    for (let c=0; c<str1.length; c++) count += (str1[c] == str2[c]) ? 0 : 1;
    return count == 1;
}

interface WordNode {
    word: string;
    value: number;
}

function ladderLength(beginWord: string, endWord: string, wordList: string[]): number {

    const hopCount: { [word: string]: number } = {
        [beginWord]: 0,
        [endWord]: Infinity
    };
    for (let word of wordList) hopCount[word] = Infinity;

    const pq = new MinPriorityQueue({
        priority: word => word.value
    });
    pq.enqueue({word: beginWord, value: 0});

    while(!pq.isEmpty()) {
        const top = pq.dequeue().element;
        // console.log(top);
        for (let word of wordList) {
            if (validEdge(top.word, word) && hopCount[word] > top.value + 1) {
                pq.enqueue({word: word, value: top.value + 1});
                hopCount[word] = top.value + 1;
            }
        }
        // console.log(hopCount);
        // console.log("-------------------------------");

    }

    // console.log(hopCount);

    return hopCount[endWord] == Infinity ? 0 : hopCount[endWord] + 1;
};