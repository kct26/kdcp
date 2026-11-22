"use client";
import { useEffect, useRef } from "react";
import { EditorView, basicSetup } from "codemirror";
import { keymap } from "@codemirror/view";
import { EditorState, Prec } from "@codemirror/state";
import { indentWithTab } from "@codemirror/commands";
import { indentUnit } from "@codemirror/language";
import { cpp } from "@codemirror/lang-cpp";

/** C++ code editor (CodeMirror 6): auto-indent, Tab / Shift+Tab, bracket closing, line numbers. */
export function CodeEditor({
  value,
  onChange,
  onSubmit,
  className = "",
}: {
  value: string;
  onChange: (v: string) => void;
  onSubmit: () => void;
  className?: string;
}) {
  const host = useRef<HTMLDivElement>(null);
  const view = useRef<EditorView | null>(null);
  const callbacks = useRef({ onChange, onSubmit });
  callbacks.current = { onChange, onSubmit };

  useEffect(() => {
    const v = new EditorView({
      parent: host.current!,
      state: EditorState.create({
        doc: value,
        extensions: [
          basicSetup,
          Prec.highest(
            keymap.of([
              { key: "Mod-Enter", run: () => (callbacks.current.onSubmit(), true) },
              indentWithTab,
            ]),
          ),
          cpp(),
          indentUnit.of("    "),
          EditorState.tabSize.of(4),
          EditorView.updateListener.of((u) => {
            if (u.docChanged) callbacks.current.onChange(u.state.doc.toString());
          }),
          EditorView.theme({
            "&": { fontSize: "14px", backgroundColor: "#ffffff", height: "100%" },
            "&.cm-focused": { outline: "none" },
            ".cm-scroller": { fontFamily: "var(--font-mono)", lineHeight: "1.65", overflow: "auto" },
            ".cm-content": { padding: "10px 0" },
            ".cm-gutters": { backgroundColor: "#f3f5f7", color: "#8a94a6", border: "none", borderRight: "1px solid #e4e8ee" },
            ".cm-activeLine": { backgroundColor: "#f5f8fc" },
            ".cm-activeLineGutter": { backgroundColor: "#e8eef6", color: "#39424e" },
          }),
        ],
      }),
    });
    view.current = v;
    return () => v.destroy();
    // the editor is created once; later value changes are synced below
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, []);

  // Apply outside changes (saved code loaded, Reset) without disturbing normal typing.
  useEffect(() => {
    const v = view.current;
    if (v && v.state.doc.toString() !== value)
      v.dispatch({ changes: { from: 0, to: v.state.doc.length, insert: value } });
  }, [value]);

  return (
    <div ref={host} aria-label="C++ source code" className={`min-h-0 overflow-hidden ${className}`} />
  );
}
