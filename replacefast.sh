#!/bin/sh
# cd ..
files=$(find src -name "*.re" && find src -name "*.rei")
echo $files
for file in $files
do
echo $PWD/$file

# fastreplacestring $file "ReasonReact.NoUpdate" "NoUpdate"
fastreplacestring $file "ReasonReact.Update" "Update"
fastreplacestring $file "ReasonReact.UpdateWithSideEffects" "UpdateWithSideEffects"
fastreplacestring $file "ReactEventRe.Synthetic" "ReactEvent.Synthetic"
fastreplacestring $file "ReactEventRe" "ReactEvent"
fastreplacestring $file "Js.Null_undefined.to_opt" "Js.Nullable.toOption"
fastreplacestring $file "Js.Nullable.to_opt" "Js.Nullable.toOption"
fastreplacestring $file "Js.Null_undefined.to_opt" "Js.Nullable.toOption"
fastreplacestring $file "ReactEventRe.Mouse.stopPropagation" "ReactEvent.Mouse.stopPropagation"
fastreplacestring $file "ReasonReact.null" "React.null"
fastreplacestring $file "ReasonReact.nullElement" "React.null"
fastreplacestring $file "ReasonReact.stringToElement" "React.string"
fastreplacestring $file "ReasonReact.string" "React.string"
fastreplacestring $file "ReasonReact.arrayToElement" "React.array"
fastreplacestring $file "ReasonReact.array" "React.array"
fastreplacestring $file "ReasonReact.reactElement" "React.element"

done
